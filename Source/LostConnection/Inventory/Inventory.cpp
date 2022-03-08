// Copyright (c) 2022 Use-your-imagination

#include "Inventory.h"

#include "Weapons/Pistols/Gauss.h"
#include "Weapons/SubmachineGuns/Hipter.h"
#include "Characters/BaseCharacter.h"
#include "AssetLoading/LostConnectionAssetManager.h"

void UInventory::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventory, primaryWeaponCell);

	DOREPLIFETIME(UInventory, secondaryWeaponCell);

	DOREPLIFETIME(UInventory, defaultWeaponCell);

	DOREPLIFETIME(UInventory, lootPoints);

	DOREPLIFETIME(UInventory, spareAmmo);

	DOREPLIFETIME(UInventory, personalModules);

	DOREPLIFETIME(UInventory, weaponModules);
}

UInventory::UInventory()
{
	primaryWeaponCell = CreateDefaultSubobject<UInventoryCell>("PrimaryWeaponCell");

	secondaryWeaponCell = CreateDefaultSubobject<UInventoryCell>("SecondaryWeaponCell");

	defaultWeaponCell = CreateDefaultSubobject<UInventoryCell>("DefaultWeaponCell");
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
	personalModules.Add(module);
}

void UInventory::addWeaponModule(UBaseWeaponModule* module)
{
	weaponModules.Add(module);
}

void UInventory::setPrimaryWeaponCell(UBaseWeapon* weapon)
{
	primaryWeaponCell->setItem(weapon);
}

void UInventory::setSecondaryWeaponCell(UBaseWeapon* weapon)
{
	secondaryWeaponCell->setItem(weapon);
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

int32 UInventory::getLootPoints() const
{
	return lootPoints;
}

const TArray<UBasePersonalModule*>& UInventory::getPersonalModules() const
{
	return personalModules;
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

	for (UBasePersonalModule* personalModule : personalModules)
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
