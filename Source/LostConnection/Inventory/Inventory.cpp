// Copyright (c) 2022 Use Your Imagination

#include "Inventory.h"

#include "Algo/Copy.h"

#include "Weapons/Pistols/Gauss.h"
#include "Weapons/SubmachineGuns/Hipter.h"
#include "Characters/BaseCharacter.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "Constants/Constants.h"

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

	DOREPLIFETIME(AInventory, personalEquippedModules);

	DOREPLIFETIME(AInventory, personalUnequippedModules);

	DOREPLIFETIME(AInventory, weaponModules);

	DOREPLIFETIME(AInventory, maxSmallAmmoCount);

	DOREPLIFETIME(AInventory, maxLargeAmmoCount);

	DOREPLIFETIME(AInventory, maxEnergyAmmoCount);
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

TArray<TObjectPtr<UInventoryCell>> AInventory::upgradeModules(const TArray<TObjectPtr<UInventoryCell>>& modules)
{
	TArray<TObjectPtr<UInventoryCell>> modulesToRemove;



	return modulesToRemove;
}

void AInventory::onUnequippedWeaponsUpdate()
{
	for (UEscapableWidget*& widget : playerState->getEscapableWidgets())
	{
		widget->onNetUpdate();
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
	UBaseWeapon* defaultWeapon = NewObject<UBaseWeapon>(this, manager.getWeaponClass(UGauss::StaticClass()));

	this->playerState = playerState;

	maxSmallAmmoCount = defaults.getMaxSmallAmmoCount();
	maxLargeAmmoCount = defaults.getMaxLargeAmmoCount();
	maxEnergyAmmoCount = defaults.getMaxEnergyAmmoCount();

	defaultWeaponCell->setItem(defaultWeapon);
}

void AInventory::addPersonalModule_Implementation(UBasePersonalModule* module)
{
	TObjectPtr<UInventoryCell> personalModuleCell = NewObject<UInventoryCell>(this);
	TArray<TObjectPtr<UInventoryCell>> modules;

	personalModuleCell->setItem(module);

	personalUnequippedModules.Add(personalModuleCell);

	modules.Reserve(personalEquippedModules.Num() + personalUnequippedModules.Num());

	Algo::Copy(personalEquippedModules, modules);

	Algo::Copy(personalUnequippedModules, modules);

	for (TObjectPtr<UInventoryCell> moduleToRemove : upgradeModules(modules))
	{
		if (!personalEquippedModules.Remove(moduleToRemove))
		{
			personalUnequippedModules.Remove(moduleToRemove);
		}
	}
}

void AInventory::addWeaponModule_Implementation(UBaseWeaponModule* module)
{
	UInventoryCell* weaponModuleCell = NewObject<UInventoryCell>(this);
	TArray<UInventoryCell*> modulesToRemove;

	weaponModuleCell->setItem(module);

	weaponModules.Add(weaponModuleCell);

	modulesToRemove = upgradeModules(weaponModules);

	for (UInventoryCell* moduleToRemove : modulesToRemove)
	{
		weaponModules.Remove(moduleToRemove);
	}
}

void AInventory::addUnequippedWeapon_Implementation(UBaseWeapon* weapon)
{
	UInventoryCell* weaponCell = NewObject<UInventoryCell>(this);

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
	return personalEquippedModules;
}

const TArray<TObjectPtr<UInventoryCell>>& AInventory::getPersonalUnequippedModules() const
{
	return personalUnequippedModules;
}

const TArray<TObjectPtr<UInventoryCell>>& AInventory::getWeaponModules() const
{
	return weaponModules;
}

ALostConnectionPlayerState* AInventory::getPlayerState() const
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

bool AInventory::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (IsValid(primaryWeaponCell))
	{
		wroteSomething |= Channel->ReplicateSubobject(primaryWeaponCell, *Bunch, *RepFlags);

		wroteSomething |= primaryWeaponCell->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(secondaryWeaponCell))
	{
		wroteSomething |= Channel->ReplicateSubobject(secondaryWeaponCell, *Bunch, *RepFlags);

		wroteSomething |= secondaryWeaponCell->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(defaultWeaponCell))
	{
		wroteSomething |= Channel->ReplicateSubobject(defaultWeaponCell, *Bunch, *RepFlags);

		wroteSomething |= defaultWeaponCell->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(firstInactiveWeaponCell))
	{
		wroteSomething |= Channel->ReplicateSubobject(firstInactiveWeaponCell, *Bunch, *RepFlags);

		wroteSomething |= firstInactiveWeaponCell->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(secondInactiveWeaponCell))
	{
		wroteSomething |= Channel->ReplicateSubobject(secondInactiveWeaponCell, *Bunch, *RepFlags);

		wroteSomething |= secondInactiveWeaponCell->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	for (TObjectPtr<UInventoryCell> cell : unequippedWeapons)
	{
		if (IsValid(cell))
		{
			wroteSomething |= Channel->ReplicateSubobject(cell, *Bunch, *RepFlags);

			wroteSomething |= cell->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	for (TObjectPtr<UInventoryCell> cell : personalEquippedModules)
	{
		if (IsValid(cell))
		{
			wroteSomething |= Channel->ReplicateSubobject(cell, *Bunch, *RepFlags);

			wroteSomething |= cell->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}
	for (TObjectPtr<UInventoryCell> cell : personalUnequippedModules)
	{
		if (IsValid(cell))
		{
			wroteSomething |= Channel->ReplicateSubobject(cell, *Bunch, *RepFlags);

			wroteSomething |= cell->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	for (TObjectPtr<UInventoryCell> cell : weaponModules)
	{
		if (IsValid(cell))
		{
			wroteSomething |= Channel->ReplicateSubobject(cell, *Bunch, *RepFlags);

			wroteSomething |= cell->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	return wroteSomething;
}
