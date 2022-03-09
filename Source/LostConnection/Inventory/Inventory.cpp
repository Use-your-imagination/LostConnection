// Copyright (c) 2022 Use-your-imagination

#include "Inventory.h"

#include "Algo/Copy.h"

#include "Weapons/Pistols/Gauss.h"
#include "Weapons/SubmachineGuns/Hipter.h"
#include "Characters/BaseCharacter.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "Constants/Constants.h"

template<typename ModuleT>
static TArray<UBaseModule*> upgradeModules(const TArray<ModuleT*>& modules);

void UInventory::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventory, primaryWeaponCell);

	DOREPLIFETIME(UInventory, secondaryWeaponCell);

	DOREPLIFETIME(UInventory, defaultWeaponCell);

	DOREPLIFETIME(UInventory, firstInactiveWeaponCell);

	DOREPLIFETIME(UInventory, secondInactiveWeaponCell);

	DOREPLIFETIME(UInventory, lootPoints);

	DOREPLIFETIME(UInventory, spareAmmo);

	DOREPLIFETIME(UInventory, personalEquippedModules);

	DOREPLIFETIME(UInventory, personalUnequippedModules);

	DOREPLIFETIME(UInventory, weaponModules);
}

UInventory::UInventory()
{
	primaryWeaponCell = CreateDefaultSubobject<UInventoryCell>("PrimaryWeaponCell");

	secondaryWeaponCell = CreateDefaultSubobject<UInventoryCell>("SecondaryWeaponCell");

	defaultWeaponCell = CreateDefaultSubobject<UInventoryCell>("DefaultWeaponCell");

	firstInactiveWeaponCell = CreateDefaultSubobject<UInventoryCell>("FirstInactiveWeaponCell");

	secondInactiveWeaponCell = CreateDefaultSubobject<UInventoryCell>("SecondInactiveWeaponCell");
}

void UInventory::init(APlayerState* playerState)
{
	ULostConnectionAssetManager& manager = ULostConnectionAssetManager::get();
	UBaseWeapon* tem = NewObject<UBaseWeapon>(playerState, manager.getWeaponClass(UHipter::StaticClass()));

	tem->updateTimeBetweenShots();

	primaryWeaponCell->setItem(tem);

	tem = NewObject<UBaseWeapon>(playerState, manager.getWeaponClass(UGauss::StaticClass()));

	tem->updateTimeBetweenShots();

	defaultWeaponCell->setItem(tem);
}

void UInventory::addPersonalModule(UBasePersonalModule* module)
{
	personalUnequippedModules.Add(module);

	TArray<UBaseModule*> modules;

	modules.Reserve(personalEquippedModules.Num() + personalUnequippedModules.Num());

	Algo::Copy(personalEquippedModules, modules);

	Algo::Copy(personalUnequippedModules, modules);

	TArray<UBaseModule*> modulesToRemove = upgradeModules(modules);

	for (UBaseModule* moduleToRemove : modulesToRemove)
	{
		if (!personalEquippedModules.Remove(Cast<UBasePersonalModule>(moduleToRemove)))
		{
			personalUnequippedModules.Remove(Cast<UBasePersonalModule>(moduleToRemove));
		}
	}
}

void UInventory::addWeaponModule(UBaseWeaponModule* module)
{
	weaponModules.Add(module);

	TArray<UBaseModule*> modulesToRemove = upgradeModules(weaponModules);

	for (UBaseModule* moduleToRemove : modulesToRemove)
	{
		weaponModules.Remove(Cast<UBaseWeaponModule>(moduleToRemove));
	}
}

void UInventory::setPrimaryWeaponCell(UBaseWeapon* weapon)
{
	primaryWeaponCell->setItem(weapon);
}

void UInventory::setSecondaryWeaponCell(UBaseWeapon* weapon)
{
	secondaryWeaponCell->setItem(weapon);
}

void UInventory::setFirstInactiveWeaponCell(UBaseWeapon* weapon)
{
	firstInactiveWeaponCell->setItem(weapon);
}

void UInventory::setSecondInactiveWeaponCell(UBaseWeapon* weapon)
{
	secondInactiveWeaponCell->setItem(weapon);
}

void UInventory::setLootPoints(int32 lootPoints)
{
	this->lootPoints = FMath::Max(0, lootPoints);
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

const TArray<UBasePersonalModule*>& UInventory::getPersonalEquippedModules() const
{
	return personalEquippedModules;
}

const TArray<UBasePersonalModule*>& UInventory::getPersonalUnequippedModules() const
{
	return personalUnequippedModules;
}

const TArray<UBaseWeaponModule*>& UInventory::getWeaponModules() const
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

	for (UBasePersonalModule* personalModule : personalEquippedModules)
	{
		if (IsValid(personalModule))
		{
			wroteSomething |= Channel->ReplicateSubobject(personalModule, *Bunch, *RepFlags);

			wroteSomething |= personalModule->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}
	for (UBasePersonalModule* personalModule : personalUnequippedModules)
	{
		if (IsValid(personalModule))
		{
			wroteSomething |= Channel->ReplicateSubobject(personalModule, *Bunch, *RepFlags);

			wroteSomething |= personalModule->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	for (UBaseWeaponModule* weaponModule : weaponModules)
	{
		if (IsValid(weaponModule))
		{
			wroteSomething |= Channel->ReplicateSubobject(weaponModule, *Bunch, *RepFlags);

			wroteSomething |= weaponModule->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	return wroteSomething;
}

template<typename ModuleT>
TArray<UBaseModule*> upgradeModules(const TArray<ModuleT*>& modules)
{
	TArray<UBaseModule*> result;

	return result;
}
