// Copyright (c) 2022 Use Your Imagination

#include "Inventory.h"

#include "Algo/Copy.h"

#include "Weapons/Pistols/Gauss.h"
#include "Weapons/SubmachineGuns/Hipter.h"
#include "Characters/BaseCharacter.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "Constants/Constants.h"

template<typename... Args>
static TArray<TObjectPtr<UInventoryCell>*> fillModules(TArray<TObjectPtr<UInventoryCell>>& modules, Args&... args);

void AInventory::updateActivePersonalModules()
{
	activePersonalModules.Empty();

	for (TObjectPtr<UInventoryCell> cell : equippedPersonalModules)
	{
		if (cell->isEmpty())
		{
			continue;
		}

		const FText& name = cell->getItem()->getItemName();

		for (TObjectPtr<UInventoryCell> uneqippedCell : unequippedPersonalModules)
		{
			if (uneqippedCell->getItem()->getItemName().EqualTo(name, ETextComparisonLevel::Type::Quinary))
			{
				activePersonalModules.Add(uneqippedCell);
			}
		}
	}
}

bool AInventory::swapBetweenUnequippedWeaponsAndSlot(TObjectPtr<UInventoryCell>& slot, UBaseWeapon* weapon)
{
	TObjectPtr<UInventoryCell>* weaponCell = unequippedWeapons.FindByPredicate([weapon](const TObjectPtr<UInventoryCell>& cell)
		{
			return cell->getItem() == weapon;
		});

	if (weaponCell)
	{
		if (TObjectPtr<UBaseWeapon> slotWeapon = slot->getItem<UBaseWeapon>())
		{
			playerState->returnAmmoToSpare(slotWeapon);

			Swap(slot, *weaponCell);
		}
		else
		{
			slot = *weaponCell;

			unequippedWeapons.RemoveSingle(slot);
		}
	}

	return StaticCast<bool>(weaponCell);
}

TArray<TObjectPtr<UInventoryCell>> AInventory::upgradeModules(const TArray<TObjectPtr<UInventoryCell>*>& modules)
{
	static int32 modulesToNextTier = ULostConnectionAssetManager::get().getDefaults().getModulesToNextTier();
	TArray<TObjectPtr<UInventoryCell>> modulesToRemove;

	for (TObjectPtr<UInventoryCell>* module : modules)
	{
		if (modulesToRemove.Contains(*module))
		{
			continue;
		}

		TObjectPtr<UBaseModule> baseModule = (*module)->getItem<UBaseModule>();
		EModuleQuality quality = baseModule->getQuality();
		TSubclassOf<UBaseModule> moduleClass = baseModule->StaticClass();
		TArray<TObjectPtr<UInventoryCell>> currentQualityModules;

		for (int32 i = 0; i < modulesToNextTier; i++)
		{
			TObjectPtr<UInventoryCell>* const* result = modules.FindByPredicate([&quality, &moduleClass, &currentQualityModules](TObjectPtr<UInventoryCell>* cell)
				{
					TObjectPtr<UBaseModule> tem = (*cell)->getItem<UBaseModule>();

					return tem->getQuality() == quality &&
						moduleClass == tem->StaticClass() &&
						!currentQualityModules.Contains(*cell);
				});

			if (result)
			{
				currentQualityModules.Add(**result);
			}
		}

		if (currentQualityModules.Num() != modulesToNextTier)
		{
			continue;
		}

		int32 possibleEquippedModuleIndex = 0;

		for (int32 i = 1; i < currentQualityModules.Num(); i++)
		{
			if (!currentQualityModules[i]->getIsEquipped())
			{
				possibleEquippedModuleIndex = i;

				break;
			}
		}

		currentQualityModules.RemoveAt(possibleEquippedModuleIndex);

		modulesToRemove.Append(MoveTemp(currentQualityModules));

		this->upgradeModule(*module);
	}

	return modulesToRemove;
}

void AInventory::upgradeModule(TObjectPtr<UInventoryCell>& moduleToUpgrade)
{
	TObjectPtr<UBaseModule> module = moduleToUpgrade->getItem<UBaseModule>();
	EModuleQuality quality = module->getQuality();

	if (quality == EModuleQuality::gold)
	{
		static const TMap<TSubclassOf<UBasePersonalModule>, TSubclassOf<UBasePersonalModule>>& personalModules = ULostConnectionAssetManager::get().getLoot().getPersonalModules();
		static const TMap<TSubclassOf<UBaseWeaponModule>, TSubclassOf<UBaseWeaponModule>>& weaponModules = ULostConnectionAssetManager::get().getLoot().getWeaponModules();
		TSubclassOf<UBaseModule> moduleClass;

		if (const TSubclassOf<UBasePersonalModule>* platinumModuleClass = personalModules.Find(module->GetClass()))
		{
			moduleClass = *platinumModuleClass;
		}
		else
		{
			moduleClass = weaponModules[module->GetClass()];
		}

		moduleToUpgrade->setItem(NewObject<UBaseModule>(this, moduleClass));
	}
	else
	{
		module->setQuality(static_cast<EModuleQuality>(static_cast<int8>(quality) + 1));
	}
}

void AInventory::onInventoryUpdate()
{
	for (TObjectPtr<UEscapableWidget>& widget : playerState->getEscapableWidgets())
	{
		widget->onNetUpdate();
	}
}

bool AInventory::containsItem(TObjectPtr<UInventoryCell> itemToFind, const TArray<TObjectPtr<UInventoryCell>>& cells)
{
	if (itemToFind->getItem() == nullptr)
	{
		return false;
	}

	TScriptInterface<IInventoriable> item = itemToFind->getItem();

	for (const TObjectPtr<UInventoryCell>& cell : cells)
	{
		if (cell->getItem() == item)
		{
			return true;
		}
	}

	return false;
}

void AInventory::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInventory, playerState);

	DOREPLIFETIME(AInventory, primaryWeaponCell);

	DOREPLIFETIME(AInventory, secondaryWeaponCell);

	DOREPLIFETIME(AInventory, defaultWeaponCell);

	DOREPLIFETIME(AInventory, firstInactiveWeaponCell);

	DOREPLIFETIME(AInventory, secondInactiveWeaponCell);

	DOREPLIFETIME(AInventory, unequippedWeapons);

	DOREPLIFETIME(AInventory, lootPoints);

	DOREPLIFETIME(AInventory, spareAmmo);

	DOREPLIFETIME(AInventory, equippedPersonalModules);

	DOREPLIFETIME(AInventory, unequippedPersonalModules);

	DOREPLIFETIME(AInventory, weaponModules);

	DOREPLIFETIME(AInventory, maxSmallAmmoCount);

	DOREPLIFETIME(AInventory, maxLargeAmmoCount);

	DOREPLIFETIME(AInventory, maxEnergyAmmoCount);
}

void AInventory::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		return;
	}

	for (int32 i = 0; i < ULostConnectionAssetManager::get().getDefaults().getPersonalModulesLimit(); i++)
	{
		equippedPersonalModules.Add(NewObject<UInventoryCell>(this));
	}
}

AInventory::AInventory()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	bAlwaysRelevant = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;

	primaryWeaponCell = CreateDefaultSubobject<UInventoryCell>("PrimaryWeaponCell");

	secondaryWeaponCell = CreateDefaultSubobject<UInventoryCell>("SecondaryWeaponCell");

	defaultWeaponCell = CreateDefaultSubobject<UInventoryCell>("DefaultWeaponCell");

	firstInactiveWeaponCell = CreateDefaultSubobject<UInventoryCell>("FirstInactiveWeaponCell");

	secondInactiveWeaponCell = CreateDefaultSubobject<UInventoryCell>("SecondInactiveWeaponCell");
}

void AInventory::init(TObjectPtr<ALostConnectionPlayerState> playerState)
{
	ULostConnectionAssetManager& manager = ULostConnectionAssetManager::get();
	const UDefaultsDataAsset& defaults = manager.getDefaults();
	TObjectPtr<UBaseWeapon> defaultWeapon = Utility::createWeapon(manager.getWeaponClass(UGauss::StaticClass()), EWeaponRarity::normal, this);

	this->playerState = playerState;

	maxSmallAmmoCount = defaults.getMaxSmallAmmoCount();
	maxLargeAmmoCount = defaults.getMaxLargeAmmoCount();
	maxEnergyAmmoCount = defaults.getMaxEnergyAmmoCount();

	defaultWeaponCell->setItem(defaultWeapon);
}

void AInventory::updateActiveWeaponModules()
{
	activeWeaponModules.Empty();

	TObjectPtr<ABaseCharacter> character = playerState->GetPawn<ABaseCharacter>();

	if (character.IsNull())
	{
		return;
	}

	TObjectPtr<UBaseWeapon> weapon = character->getCurrentWeapon();

	if (weapon.IsNull())
	{
		return;
	}

	for (TObjectPtr<UInventoryCell>& cell : weaponModules)
	{
		const FText& name = cell->getItem()->getItemName();

		for (TObjectPtr<UInventoryCell>& uneqippedCell : weapon->getWeaponModules())
		{
			TScriptInterface<IInventoriable> currentWeaponModule = uneqippedCell->getItem();

			if (currentWeaponModule && (uneqippedCell != cell) && currentWeaponModule->getItemName().EqualTo(name, ETextComparisonLevel::Type::Quinary))
			{
				activeWeaponModules.Add(uneqippedCell);
			}
		}
	}
}

void AInventory::equipOrUnequipPersonalModule_Implementation(UInventoryCell* module)
{
	if (TObjectPtr<UInventoryCell>* cell = equippedPersonalModules.FindByKey(module))
	{
		TObjectPtr<UInventoryCell> newCell = NewObject<UInventoryCell>(this);

		newCell->setItem((*cell)->getItem().GetInterface());

		unequippedPersonalModules.Add(newCell);

		(*cell)->setItem(nullptr);

		(*cell)->unequip();
	}
	else
	{
		int32 index = unequippedPersonalModules.Find(module);

		for (TObjectPtr<UInventoryCell> equippedModule : equippedPersonalModules)
		{
			if (equippedModule->isEmpty())
			{
				equippedModule->setItem(unequippedPersonalModules[index]->getItem().GetInterface());

				equippedModule->equip();

				unequippedPersonalModules.RemoveAt(index);

				break;
			}
		}
	}

	this->updateActivePersonalModules();
}

void AInventory::swapPersonalModules_Implementation(UInventoryCell* firstModule, UInventoryCell* secondModule)
{
	auto findModule = [this](TObjectPtr<UInventoryCell> cell) -> TObjectPtr<UInventoryCell>&
	{
		TObjectPtr<UInventoryCell>* result = equippedPersonalModules.FindByKey(cell);

		if (!result)
		{
			result = unequippedPersonalModules.FindByKey(cell);
		}

		return *result;
	};
	TObjectPtr<UInventoryCell>& first = findModule(firstModule);
	TObjectPtr<UInventoryCell>& second = findModule(secondModule);

	if (first->isEmpty() || second->isEmpty())
	{
		TObjectPtr<UInventoryCell>& empty = first->isEmpty() ? first : second;
		TObjectPtr<UInventoryCell>& notEmpty = first->isEmpty() ? second : first;
		int32 index = unequippedPersonalModules.Find(notEmpty);

		empty->setItem(notEmpty->getItem().GetInterface());

		empty->equip();

		notEmpty->setItem(nullptr);

		notEmpty->unequip();

		if (index != INDEX_NONE)
		{
			unequippedPersonalModules.RemoveAt(index);
		}
	}
	else
	{
		auto changeEquipState = [this](TObjectPtr<UInventoryCell>& cell)
		{
			if (equippedPersonalModules.Contains(cell))
			{
				cell->equip();
			}
			else
			{
				cell->unequip();
			}
		};

		Swap(first, second);

		changeEquipState(first);

		changeEquipState(second);
	}

	this->updateActivePersonalModules();
}

void AInventory::equipOrUnequipWeaponModule_Implementation(UInventoryCell* selectedWeapon, UInventoryCell* module)
{
	if (!IsValid(selectedWeapon))
	{
		this->updateActiveWeaponModules();

		return;
	}

	TArray<TObjectPtr<UInventoryCell>>& modules = selectedWeapon->getItem<UBaseWeapon>()->getWeaponModules();

	if (weaponModules.Contains(module))
	{
		if (AInventory::containsItem(module, modules))
		{
			return;
		}

		for (TObjectPtr<UInventoryCell> weaponModule : modules)
		{
			if (weaponModule->isEmpty())
			{
				weaponModule->setItem(module->getItem().GetInterface());

				weaponModule->equip();

				break;
			}
		}
	}
	else
	{
		TObjectPtr<UInventoryCell>* cell = modules.FindByKey(module);

		(*cell)->setItem(nullptr);

		(*cell)->unequip();
	}

	this->updateActiveWeaponModules();
}

void AInventory::swapWeaponModules_Implementation(UInventoryCell* selectedWeapon, UInventoryCell* firstModule, UInventoryCell* secondModule)
{
	if (!IsValid(selectedWeapon))
	{
		this->updateActiveWeaponModules();

		return;
	}

	TArray<TObjectPtr<UInventoryCell>>& modules = selectedWeapon->getItem<UBaseWeapon>()->getWeaponModules();
	auto findModule = [this, &modules](TObjectPtr<UInventoryCell> cell) -> TObjectPtr<UInventoryCell>&
	{
		TObjectPtr<UInventoryCell>* result = modules.FindByKey(cell);

		if (!result)
		{
			result = weaponModules.FindByKey(cell);
		}

		return *result;
	};
	auto checkDublicate = [this, &modules](TObjectPtr<UInventoryCell> cell)
	{
		return weaponModules.Contains(cell) && AInventory::containsItem(cell, modules);
	};
	TObjectPtr<UInventoryCell>& first = findModule(firstModule);
	TObjectPtr<UInventoryCell>& second = findModule(secondModule);
	bool isSamePlace = (weaponModules.Contains(first) && weaponModules.Contains(second)) || (modules.Contains(first) && modules.Contains(second));

	if (!isSamePlace && (checkDublicate(first) || checkDublicate(second)))
	{
		return;
	}

	if (first->isEmpty() || second->isEmpty())
	{
		TObjectPtr<UInventoryCell>& empty = first->isEmpty() ? first : second;
		TObjectPtr<UInventoryCell>& notEmpty = first->isEmpty() ? second : first;

		empty->setItem(notEmpty->getItem().GetInterface());

		empty->equip();

		notEmpty->unequip();

		if (isSamePlace)
		{
			notEmpty->setItem(nullptr);
		}
	}
	else
	{
		if (isSamePlace)
		{
			Swap(first, second);
		}
		else
		{
			if (modules.Contains(first))
			{
				first->setItem(second->getItem().GetInterface());

				first->equip();

				second->unequip();
			}
			else
			{
				second->setItem(first->getItem().GetInterface());

				second->equip();

				first->unequip();
			}
		}
	}

	this->updateActiveWeaponModules();
}

void AInventory::addPersonalModule_Implementation(UBasePersonalModule* module)
{
	TObjectPtr<UInventoryCell> personalModuleCell = NewObject<UInventoryCell>(this);

	personalModuleCell->setItem(module);

	unequippedPersonalModules.Add(personalModuleCell);

	for (TObjectPtr<UInventoryCell> moduleToRemove : this->upgradeModules(fillModules(equippedPersonalModules, unequippedPersonalModules)))
	{
		if (!equippedPersonalModules.RemoveSingle(moduleToRemove))
		{
			unequippedPersonalModules.RemoveSingle(moduleToRemove);
		}
	}

	this->updateActivePersonalModules();
}

void AInventory::addWeaponModule_Implementation(UBaseWeaponModule* module)
{
	TObjectPtr<UInventoryCell> weaponModuleCell = NewObject<UInventoryCell>(this);

	weaponModuleCell->setItem(module);

	weaponModules.Add(weaponModuleCell);

	for (TObjectPtr<UInventoryCell> moduleToRemove : this->upgradeModules(fillModules(weaponModules)))
	{
		weaponModules.Remove(moduleToRemove);
	}

	this->updateActiveWeaponModules();
}

void AInventory::addUnequippedWeapon_Implementation(UBaseWeapon* weapon)
{
	TObjectPtr<UInventoryCell> weaponCell = NewObject<UInventoryCell>(this);

	weaponCell->setItem(weapon);

	unequippedWeapons.Add(weaponCell);
}

void AInventory::setPrimaryWeaponCell_Implementation(UBaseWeapon* weapon)
{
	if (this->swapBetweenUnequippedWeaponsAndSlot(primaryWeaponCell, weapon))
	{
		return;
	}

	primaryWeaponCell->setItem(weapon);
}

void AInventory::setSecondaryWeaponCell_Implementation(UBaseWeapon* weapon)
{
	if (this->swapBetweenUnequippedWeaponsAndSlot(secondaryWeaponCell, weapon))
	{
		return;
	}

	secondaryWeaponCell->setItem(weapon);
}

void AInventory::setFirstInactiveWeaponCell_Implementation(UBaseWeapon* weapon)
{
	if (this->swapBetweenUnequippedWeaponsAndSlot(firstInactiveWeaponCell, weapon))
	{
		return;
	}

	firstInactiveWeaponCell->setItem(weapon);
}

void AInventory::setSecondInactiveWeaponCell_Implementation(UBaseWeapon* weapon)
{
	if (this->swapBetweenUnequippedWeaponsAndSlot(secondInactiveWeaponCell, weapon))
	{
		return;
	}

	secondInactiveWeaponCell->setItem(weapon);
}

void AInventory::setLootPoints_Implementation(int32 newLootPoints)
{
	lootPoints = FMath::Max(0, newLootPoints);
}

void AInventory::setMaxSmallAmmoCount_Implementation(int32 count)
{
	maxSmallAmmoCount = count;
}

void AInventory::setMaxLargeAmmoCount_Implementation(int32 count)
{
	maxLargeAmmoCount = count;
}

void AInventory::setMaxEnergyAmmoCount_Implementation(int32 count)
{
	maxEnergyAmmoCount = count;
}

TObjectPtr<UInventoryCell> AInventory::getPrimaryWeaponCell() const
{
	return primaryWeaponCell;
}

TObjectPtr<UInventoryCell> AInventory::getSecondaryWeaponCell() const
{
	return secondaryWeaponCell;
}

TObjectPtr<UInventoryCell> AInventory::getDefaultWeaponCell() const
{
	return defaultWeaponCell;
}

TObjectPtr<UInventoryCell> AInventory::getFirstInactiveWeaponCell() const
{
	return firstInactiveWeaponCell;
}

TObjectPtr<UInventoryCell> AInventory::getSecondInactiveWeaponCell() const
{
	return secondInactiveWeaponCell;
}

int32 AInventory::getLootPoints() const
{
	return lootPoints;
}

const TArray<TObjectPtr<UInventoryCell>>& AInventory::getPersonalEquippedModules() const
{
	return equippedPersonalModules;
}

const TArray<TObjectPtr<UInventoryCell>>& AInventory::getPersonalUnequippedModules() const
{
	return unequippedPersonalModules;
}

const TArray<TObjectPtr<UInventoryCell>>& AInventory::getWeaponModules() const
{
	return weaponModules;
}

TObjectPtr<ALostConnectionPlayerState> AInventory::getPlayerState() const
{
	return playerState;
}

int32 AInventory::getMaxSmallAmmoCount() const
{
	return maxSmallAmmoCount;
}

int32 AInventory::getMaxLargeAmmoCount() const
{
	return maxLargeAmmoCount;
}

int32 AInventory::getMaxEnergyAmmoCount() const
{
	return maxEnergyAmmoCount;
}

int32 AInventory::getMaxAmmoCount(EAmmoType type) const
{
	switch (type)
	{
	case EAmmoType::small:
		return this->getMaxSmallAmmoCount();

	case EAmmoType::large:
		return this->getMaxLargeAmmoCount();

	case EAmmoType::energy:
		return this->getMaxEnergyAmmoCount();
	}

	return 0;
}

const TArray<TObjectPtr<UInventoryCell>>& AInventory::getActivePersonalModules() const
{
	return activePersonalModules;
}

const TArray<TObjectPtr<UInventoryCell>>& AInventory::getActiveWeaponModules() const
{
	return activeWeaponModules;
}

bool AInventory::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (primaryWeaponCell)
	{
		wroteSomething |= Channel->ReplicateSubobject(primaryWeaponCell, *Bunch, *RepFlags);

		wroteSomething |= primaryWeaponCell->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (secondaryWeaponCell)
	{
		wroteSomething |= Channel->ReplicateSubobject(secondaryWeaponCell, *Bunch, *RepFlags);

		wroteSomething |= secondaryWeaponCell->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (defaultWeaponCell)
	{
		wroteSomething |= Channel->ReplicateSubobject(defaultWeaponCell, *Bunch, *RepFlags);

		wroteSomething |= defaultWeaponCell->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (firstInactiveWeaponCell)
	{
		wroteSomething |= Channel->ReplicateSubobject(firstInactiveWeaponCell, *Bunch, *RepFlags);

		wroteSomething |= firstInactiveWeaponCell->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (secondInactiveWeaponCell)
	{
		wroteSomething |= Channel->ReplicateSubobject(secondInactiveWeaponCell, *Bunch, *RepFlags);

		wroteSomething |= secondInactiveWeaponCell->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	for (TObjectPtr<UInventoryCell> cell : unequippedWeapons)
	{
		if (cell)
		{
			wroteSomething |= Channel->ReplicateSubobject(cell, *Bunch, *RepFlags);

			wroteSomething |= cell->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	for (TObjectPtr<UInventoryCell> cell : equippedPersonalModules)
	{
		if (cell)
		{
			wroteSomething |= Channel->ReplicateSubobject(cell, *Bunch, *RepFlags);

			wroteSomething |= cell->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}
	for (TObjectPtr<UInventoryCell> cell : unequippedPersonalModules)
	{
		if (cell)
		{
			wroteSomething |= Channel->ReplicateSubobject(cell, *Bunch, *RepFlags);

			wroteSomething |= cell->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	for (TObjectPtr<UInventoryCell> cell : weaponModules)
	{
		if (cell)
		{
			wroteSomething |= Channel->ReplicateSubobject(cell, *Bunch, *RepFlags);

			wroteSomething |= cell->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	return wroteSomething;
}

template<typename... Args>
TArray<TObjectPtr<UInventoryCell>*> fillModules(TArray<TObjectPtr<UInventoryCell>>& modules, Args&... args)
{
	TArray<TObjectPtr<UInventoryCell>*> result;

	for (TObjectPtr<UInventoryCell>& module : modules)
	{
		if (module->isEmpty() || module->getItem<UBaseModule>()->getQuality() == EModuleQuality::platinum)
		{
			continue;
		}

		result.Add(&module);
	}

	if constexpr (sizeof...(args))
	{
		result.Append(fillModules(args...));
	}

	return result;
}
