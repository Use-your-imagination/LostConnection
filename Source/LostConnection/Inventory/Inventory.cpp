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

void UInventory::setPrimaryWeaponCell_Implementation(UBaseWeapon* weapon)
{
	primaryWeaponCell->setItem(weapon);
}

void UInventory::setSecondaryWeaponCell_Implementation(UBaseWeapon* weapon)
{
	secondaryWeaponCell->setItem(weapon);
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

	return wroteSomething;
}
