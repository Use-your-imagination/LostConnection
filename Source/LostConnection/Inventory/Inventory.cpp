// Copyright (c) 2022 Use-your-imagination

#include "Inventory.h"

#include "Algo/Copy.h"

#include "Weapons/Pistols/Gauss.h"
#include "Weapons/SubmachineGuns/Hipter.h"
#include "Characters/BaseCharacter.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "Constants/Constants.h"

static TArray<UInventoryCell*> upgradeModules(const TArray<UInventoryCell*>& modules);

void UInventory::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventory, primaryWeaponCell);

	DOREPLIFETIME(UInventory, secondaryWeaponCell);

	DOREPLIFETIME(UInventory, defaultWeaponCell);

	DOREPLIFETIME(UInventory, firstInactiveWeaponCell);

	DOREPLIFETIME(UInventory, secondInactiveWeaponCell);

	DOREPLIFETIME(UInventory, unequippedWeapons);

	DOREPLIFETIME(UInventory, lootPoints);

	DOREPLIFETIME(UInventory, spareAmmo);

	DOREPLIFETIME(UInventory, personalEquippedModules);

	DOREPLIFETIME(UInventory, personalUnequippedModules);

	DOREPLIFETIME(UInventory, weaponModules);
}

bool UInventory::swapBetweenUnequippedWeaponsAndSlot(UInventoryCell*& slot, UBaseWeapon* weapon)
{
	UInventoryCell** weaponCell = unequippedWeapons.FindByPredicate([weapon](const UInventoryCell* cell)
		{
			return cell->getItem() == weapon;
		});

	if (weaponCell)
	{
		if (slot->getItem())
		{
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

UInventory::UInventory()
{
	primaryWeaponCell = CreateDefaultSubobject<UInventoryCell>("PrimaryWeaponCell");

	secondaryWeaponCell = CreateDefaultSubobject<UInventoryCell>("SecondaryWeaponCell");

	defaultWeaponCell = CreateDefaultSubobject<UInventoryCell>("DefaultWeaponCell");

	firstInactiveWeaponCell = CreateDefaultSubobject<UInventoryCell>("FirstInactiveWeaponCell");

	secondInactiveWeaponCell = CreateDefaultSubobject<UInventoryCell>("SecondInactiveWeaponCell");
}

void UInventory::init(ALostConnectionPlayerState* playerState)
{
	ULostConnectionAssetManager& manager = ULostConnectionAssetManager::get();
	UBaseWeapon* defaultWeapon = NewObject<UBaseWeapon>(playerState, manager.getWeaponClass(UGauss::StaticClass()));

	this->playerState = playerState;

	defaultWeapon->updateTimeBetweenShots();

	defaultWeaponCell->setItem(defaultWeapon);
}

void UInventory::addPersonalModule_Implementation(UBasePersonalModule* module)
{
	UInventoryCell* personalModuleCell = NewObject<UInventoryCell>(playerState);
	TArray<UInventoryCell*> modules;
	TArray<UInventoryCell*> modulesToRemove;

	personalModuleCell->setItem(module);

	personalUnequippedModules.Add(personalModuleCell);

	modules.Reserve(personalEquippedModules.Num() + personalUnequippedModules.Num());

	Algo::Copy(personalEquippedModules, modules);

	Algo::Copy(personalUnequippedModules, modules);

	modulesToRemove = upgradeModules(modules);

	for (UInventoryCell* moduleToRemove : modulesToRemove)
	{
		if (!personalEquippedModules.Remove(moduleToRemove))
		{
			personalUnequippedModules.Remove(moduleToRemove);
		}
	}
}

void UInventory::addWeaponModule_Implementation(UBaseWeaponModule* module)
{
	UInventoryCell* weaponModuleCell = NewObject<UInventoryCell>(playerState);
	TArray<UInventoryCell*> modulesToRemove;

	weaponModuleCell->setItem(module);

	weaponModules.Add(weaponModuleCell);

	modulesToRemove = upgradeModules(weaponModules);

	for (UInventoryCell* moduleToRemove : modulesToRemove)
	{
		weaponModules.Remove(moduleToRemove);
	}
}

void UInventory::addUnequippedWeapon_Implementation(UBaseWeapon* weapon)
{
	UInventoryCell* weaponCell = NewObject<UInventoryCell>(playerState);

	weaponCell->setItem(weapon);

	unequippedWeapons.Add(weaponCell);
}

void UInventory::setPrimaryWeaponCell_Implementation(UBaseWeapon* weapon)
{
	if (this->swapBetweenUnequippedWeaponsAndSlot(primaryWeaponCell, weapon))
	{
		return;
	}

	primaryWeaponCell->setItem(weapon);
}

void UInventory::setSecondaryWeaponCell_Implementation(UBaseWeapon* weapon)
{
	if (this->swapBetweenUnequippedWeaponsAndSlot(secondaryWeaponCell, weapon))
	{
		return;
	}

	secondaryWeaponCell->setItem(weapon);
}

void UInventory::setFirstInactiveWeaponCell_Implementation(UBaseWeapon* weapon)
{
	if (this->swapBetweenUnequippedWeaponsAndSlot(firstInactiveWeaponCell, weapon))
	{
		return;
	}

	firstInactiveWeaponCell->setItem(weapon);
}

void UInventory::setSecondInactiveWeaponCell_Implementation(UBaseWeapon* weapon)
{
	if (this->swapBetweenUnequippedWeaponsAndSlot(secondInactiveWeaponCell, weapon))
	{
		return;
	}

	secondInactiveWeaponCell->setItem(weapon);
}

void UInventory::setLootPoints_Implementation(int32 newLootPoints)
{
	lootPoints = FMath::Max(0, newLootPoints);
}

UInventoryCell* UInventory::getPrimaryWeaponCell() const
{
	return primaryWeaponCell;
}

UInventoryCell* UInventory::getSecondaryWeaponCell() const
{
	return secondaryWeaponCell;
}

UInventoryCell* UInventory::getDefaultWeaponCell() const
{
	return defaultWeaponCell;
}

UInventoryCell* UInventory::getFirstInactiveWeaponCell() const
{
	return firstInactiveWeaponCell;
}

UInventoryCell* UInventory::getSecondInactiveWeaponCell() const
{
	return secondInactiveWeaponCell;
}

int32 UInventory::getLootPoints() const
{
	return lootPoints;
}

const TArray<UInventoryCell*>& UInventory::getPersonalEquippedModules() const
{
	return personalEquippedModules;
}

const TArray<UInventoryCell*>& UInventory::getPersonalUnequippedModules() const
{
	return personalUnequippedModules;
}

const TArray<UInventoryCell*>& UInventory::getWeaponModules() const
{
	return weaponModules;
}

bool UInventory::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
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

	for (UInventoryCell* cell : unequippedWeapons)
	{
		if (IsValid(cell))
		{
			wroteSomething |= Channel->ReplicateSubobject(cell, *Bunch, *RepFlags);

			wroteSomething |= cell->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	for (UInventoryCell* cell : personalEquippedModules)
	{
		if (IsValid(cell))
		{
			wroteSomething |= Channel->ReplicateSubobject(cell, *Bunch, *RepFlags);

			wroteSomething |= cell->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}
	for (UInventoryCell* cell : personalUnequippedModules)
	{
		if (IsValid(cell))
		{
			wroteSomething |= Channel->ReplicateSubobject(cell, *Bunch, *RepFlags);

			wroteSomething |= cell->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	for (UInventoryCell* cell : weaponModules)
	{
		if (IsValid(cell))
		{
			wroteSomething |= Channel->ReplicateSubobject(cell, *Bunch, *RepFlags);

			wroteSomething |= cell->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	return wroteSomething;
}

ALostConnectionPlayerState* UInventory::getPlayerState() const
{
	return playerState;
}

TArray<UInventoryCell*> upgradeModules(const TArray<UInventoryCell*>& modules)
{
	TArray<UInventoryCell*> result;

	return result;
}
