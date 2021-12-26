// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionPlayerState.h"

#include "Constants/Constants.h"
#include "AssetLoading/LostConnectionAssetManager.h"

FAmmoData::FAmmoData(ammoTypes ammoType, int32 ammoCount) :
	ammoType(ammoType),
	ammoCount(ammoCount)
{

}

void ALostConnectionPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALostConnectionPlayerState, primaryWeapon);

	DOREPLIFETIME(ALostConnectionPlayerState, secondaryWeapon);

	DOREPLIFETIME(ALostConnectionPlayerState, defaultWeapon);

	DOREPLIFETIME(ALostConnectionPlayerState, mainModules);

	DOREPLIFETIME(ALostConnectionPlayerState, weaponModules);

	DOREPLIFETIME(ALostConnectionPlayerState, spareAmmo);
}

bool ALostConnectionPlayerState::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(primaryWeapon, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(secondaryWeapon, *Bunch, *RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(defaultWeapon, *Bunch, *RepFlags);
	
	if (primaryWeapon)
	{
		wroteSomething |= primaryWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (secondaryWeapon)
	{
		wroteSomething |= secondaryWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	wroteSomething |= defaultWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);

	return wroteSomething;
}

void ALostConnectionPlayerState::BeginPlay()
{
	Super::BeginPlay();

	selectorMaterial = UMaterialInstanceDynamic::Create(ULostConnectionAssetManager::get().getUI().getBaseWeaponSelectorMaterial(), this);
}

void ALostConnectionPlayerState::addMainModule(IMainModule* module)
{
	mainModules.Add(module->_getUObject());
}

void ALostConnectionPlayerState::addWeaponModule(IWeaponModule* module)
{
	weaponModules.Add(module->_getUObject());
}

void ALostConnectionPlayerState::setPrimaryWeapon(UBaseWeapon* primaryWeapon)
{
	this->primaryWeapon = primaryWeapon;
}

void ALostConnectionPlayerState::setSecondaryWeapon(UBaseWeapon* secondaryWeapon)
{
	this->secondaryWeapon = secondaryWeapon;
}

void ALostConnectionPlayerState::setDefaultWeapon(UBaseWeapon* defaultWeapon)
{
	this->defaultWeapon = defaultWeapon;
}

const TArray<UObject*>& ALostConnectionPlayerState::getMainModules() const
{
	return mainModules;
}

const TArray<UObject*>& ALostConnectionPlayerState::getWeaponModules() const
{
	return weaponModules;
}

TArray<FAmmoData>& ALostConnectionPlayerState::getSpareAmmoArray()
{
	return spareAmmo;
}

ALostConnectionPlayerState::ALostConnectionPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
}

UUserWidget* ALostConnectionPlayerState::setCurrentUI(UUserWidget* widget)
{
	currentUI = widget;

	return currentUI;
}

UUserWidget* ALostConnectionPlayerState::getCurrentUI() const
{
	return currentUI;
}
