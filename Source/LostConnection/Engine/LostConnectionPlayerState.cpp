// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionPlayerState.h"

#include "Constants/Constants.h"
#include "AssetLoading/LostConnectionAssetManager.h"

template<typename T>
static void reduceCooldownableDataObjects(float DeltaTime, TArray<T>& cooldownableData)
{
	for (int32 i = 0; i < cooldownableData.Num(); i++)
	{
		float& remainingCooldown = cooldownableData[i].remainingCooldown;

		remainingCooldown -= DeltaTime;

		if (remainingCooldown <= 0.0f)
		{
			cooldownableData.RemoveAt(i--);
		}
	}
}

void ALostConnectionPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALostConnectionPlayerState, primaryWeapon);

	DOREPLIFETIME(ALostConnectionPlayerState, secondaryWeapon);

	DOREPLIFETIME(ALostConnectionPlayerState, defaultWeapon);

	DOREPLIFETIME(ALostConnectionPlayerState, firstInactiveWeapon);

	DOREPLIFETIME(ALostConnectionPlayerState, secondInactiveWeapon);

	DOREPLIFETIME(ALostConnectionPlayerState, mainModules);

	DOREPLIFETIME(ALostConnectionPlayerState, weaponModules);

	DOREPLIFETIME(ALostConnectionPlayerState, spareAmmo);

	DOREPLIFETIME(ALostConnectionPlayerState, cooldownableAbilities);

	DOREPLIFETIME(ALostConnectionPlayerState, cooldownableWeapons);

	DOREPLIFETIME(ALostConnectionPlayerState, respawnCooldown);

	DOREPLIFETIME(ALostConnectionPlayerState, currentRespawnCooldown);
}

bool ALostConnectionPlayerState::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (IsValid(primaryWeapon))
	{
		wroteSomething |= Channel->ReplicateSubobject(primaryWeapon, *Bunch, *RepFlags);

		wroteSomething |= primaryWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(secondaryWeapon))
	{
		wroteSomething |= Channel->ReplicateSubobject(secondaryWeapon, *Bunch, *RepFlags);

		wroteSomething |= secondaryWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(defaultWeapon))
	{
		wroteSomething |= Channel->ReplicateSubobject(defaultWeapon, *Bunch, *RepFlags);

		wroteSomething |= defaultWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(firstInactiveWeapon))
	{
		wroteSomething |= Channel->ReplicateSubobject(firstInactiveWeapon, *Bunch, *RepFlags);

		wroteSomething |= firstInactiveWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(secondInactiveWeapon))
	{
		wroteSomething |= Channel->ReplicateSubobject(secondInactiveWeapon, *Bunch, *RepFlags);

		wroteSomething |= secondInactiveWeapon->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	for (UNetworkObject* mainModule : mainModules)
	{
		if (IsValid(mainModule))
		{
			wroteSomething |= Channel->ReplicateSubobject(mainModule, *Bunch, *RepFlags);

			wroteSomething |= mainModule->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	for (UNetworkObject* weaponModule : weaponModules)
	{
		if (IsValid(weaponModule))
		{
			wroteSomething |= Channel->ReplicateSubobject(weaponModule, *Bunch, *RepFlags);

			wroteSomething |= weaponModule->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	return wroteSomething;
}

void ALostConnectionPlayerState::addMainModule(IMainModule* module)
{
	mainModules.Add(Cast<UNetworkObject>(module));
}

void ALostConnectionPlayerState::addWeaponModule(IWeaponModule* module)
{
	weaponModules.Add(Cast<UNetworkObject>(module));
}

void ALostConnectionPlayerState::addCooldownableAbility(abilitySlot slot, const ICooldownable* cooldownable)
{
	if (!cooldownable->isUsable())
	{
		cooldownableAbilities.Add(FCooldownableAbilitiesData(slot, cooldownable->getCurrentCooldown()));
	}
}

void ALostConnectionPlayerState::addCooldownableWeapon(weaponSlotTypes slot, const ICooldownable* cooldownable)
{
	if (!cooldownable->isUsable())
	{
		cooldownableWeapons.Add(FCooldownableWeaponsData(slot, cooldownable->getCurrentCooldown()));
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

const TArray<FCooldownableWeaponsData>& ALostConnectionPlayerState::getCooldownableWeapons() const
{
	return cooldownableWeapons;
}

ALostConnectionPlayerState::ALostConnectionPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
}

void ALostConnectionPlayerState::init()
{
	selectorMaterial = UMaterialInstanceDynamic::Create(ULostConnectionAssetManager::get().getUI().getBaseWeaponSelectorMaterial(), this);
}

void ALostConnectionPlayerState::resetCurrentUI_Implementation()
{
	if (IsValid(currentUI))
	{
		currentUI->RemoveFromViewport();
	}

	currentUI = nullptr;
}

void ALostConnectionPlayerState::restoreRespawnCooldown_Implementation()
{
	currentRespawnCooldown = respawnCooldown;
}

void ALostConnectionPlayerState::setCurrentUI_Implementation(TSubclassOf<UUserWidget> widget, APawn* outer)
{
	this->resetCurrentUI();

	currentUI = NewObject<UUserWidget>(outer, widget);

	if (currentUI->Implements<UPlayerHolder>())
	{
		IPlayerHolder::Execute_setPlayer(currentUI, outer);
	}

	currentUI->AddToViewport();
}

void ALostConnectionPlayerState::setDroneClass_Implementation(TSubclassOf<ABaseDrone> newDroneClass)
{
	droneClass = newDroneClass;
}

void ALostConnectionPlayerState::setCurrentRespawnCooldown_Implementation(float newCurrentRespawnCooldown)
{
	currentRespawnCooldown = newCurrentRespawnCooldown;
}

UUserWidget* ALostConnectionPlayerState::getCurrentUI() const
{
	return currentUI;
}

const TSubclassOf<ABaseDrone>& ALostConnectionPlayerState::getDroneClass() const
{
	return droneClass;
}

float ALostConnectionPlayerState::getCurrentRespawnCooldown() const
{
	return currentRespawnCooldown;
}

void ALostConnectionPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		reduceCooldownableDataObjects(DeltaTime, cooldownableAbilities);

		reduceCooldownableDataObjects(DeltaTime, cooldownableWeapons);

		if (currentRespawnCooldown)
		{
			currentRespawnCooldown = FMath::Max(0.0f, currentRespawnCooldown - DeltaTime);
		}
	}
}

#pragma region Multiplayer
void ALostConnectionPlayerState::runMulticastReliable_Implementation(AActor* caller, const FName& methodName)
{
	if (!caller)
	{
		return;
	}

	FSimpleDelegate delegate;

	delegate.BindUFunction(caller, methodName);

	delegate.Execute();
}

void ALostConnectionPlayerState::runMulticastUnreliable_Implementation(AActor* caller, const FName& methodName)
{
	if (!caller)
	{
		return;
	}

	FSimpleDelegate delegate;

	delegate.BindUFunction(caller, methodName);

	delegate.Execute();
}

void ALostConnectionPlayerState::runOnServerReliableWithMulticast_Implementation(AActor* caller, const FName& methodName)
{
	this->runMulticastReliable(caller, methodName);
}

void ALostConnectionPlayerState::runOnServerUnreliableWithMulticast_Implementation(AActor* caller, const FName& methodName)
{
	this->runMulticastUnreliable(caller, methodName);
}

void ALostConnectionPlayerState::runOnServerReliable_Implementation(AActor* caller, const FName& methodName)
{
	if (!caller)
	{
		return;
	}

	FSimpleDelegate delegate;

	delegate.BindUFunction(caller, methodName);

	delegate.Execute();
}

void ALostConnectionPlayerState::runOnServerUnreliable_Implementation(AActor* caller, const FName& methodName)
{
	if (!caller)
	{
		return;
	}

	FSimpleDelegate delegate;

	delegate.BindUFunction(caller, methodName);

	delegate.Execute();
}
#pragma endregion
