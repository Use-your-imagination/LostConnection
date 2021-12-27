// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionPlayerState.h"

#include "Constants/Constants.h"
#include "AssetLoading/LostConnectionAssetManager.h"

FAmmoData::FAmmoData(ammoTypes ammoType, int32 ammoCount) :
	ammoCount(ammoCount),
	ammoType(ammoType)
{

}

FCooldownableAbilitiesData::FCooldownableAbilitiesData(abilitySlot slot, float remainingCooldown) :
	remainingCooldown(remainingCooldown),
	slot(slot)
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

	DOREPLIFETIME(ALostConnectionPlayerState, cooldownableAbilities);
}

bool ALostConnectionPlayerState::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (primaryWeapon)
	{
		wroteSomething |= Channel->ReplicateSubobject(primaryWeapon, *Bunch, *RepFlags);

		wroteSomething |= primaryWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (secondaryWeapon)
	{
		wroteSomething |= Channel->ReplicateSubobject(secondaryWeapon, *Bunch, *RepFlags);

		wroteSomething |= secondaryWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	wroteSomething |= Channel->ReplicateSubobject(defaultWeapon, *Bunch, *RepFlags);

	wroteSomething |= defaultWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (UNetworkObject* mainModule : mainModules)
	{
		wroteSomething |= Channel->ReplicateSubobject(mainModule, *Bunch, *RepFlags);

		wroteSomething |= mainModule->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	for (UNetworkObject* weaponModule : weaponModules)
	{
		wroteSomething |= Channel->ReplicateSubobject(weaponModule, *Bunch, *RepFlags);

		wroteSomething |= weaponModule->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return wroteSomething;
}

void ALostConnectionPlayerState::BeginPlay()
{
	Super::BeginPlay();

	selectorMaterial = UMaterialInstanceDynamic::Create(ULostConnectionAssetManager::get().getUI().getBaseWeaponSelectorMaterial(), this);
}

void ALostConnectionPlayerState::addMainModule(IMainModule* module)
{
	mainModules.Add(Cast<UNetworkObject>(module));
}

void ALostConnectionPlayerState::addWeaponModule(IWeaponModule* module)
{
	weaponModules.Add(Cast<UNetworkObject>(module));
}

void ALostConnectionPlayerState::addCooldownableAbility(abilitySlot slot, ICooldownable* cooldownable)
{
	if (!cooldownable->isUsable())
	{
		cooldownableAbilities.Add(FCooldownableAbilitiesData(slot, cooldownable->getCurrentCooldown()));
	}
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

const TArray<UNetworkObject*>& ALostConnectionPlayerState::getMainModules() const
{
	return mainModules;
}

const TArray<UNetworkObject*>& ALostConnectionPlayerState::getWeaponModules() const
{
	return weaponModules;
}

TArray<FAmmoData>& ALostConnectionPlayerState::getSpareAmmoArray()
{
	return spareAmmo;
}

const TArray<FCooldownableAbilitiesData>& ALostConnectionPlayerState::getCooldownableAbilities() const
{
	return cooldownableAbilities;
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

void ALostConnectionPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		for (int32 i = 0; i < cooldownableAbilities.Num(); i++)
		{
			float& remainingCooldown = cooldownableAbilities[i].remainingCooldown;

			remainingCooldown -= DeltaTime;

			if (remainingCooldown <= 0.0f)
			{
				cooldownableAbilities.RemoveAt(i--);
			}
		}
	}
}
