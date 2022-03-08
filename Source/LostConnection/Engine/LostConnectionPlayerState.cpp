// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionPlayerState.h"

#include "Constants/Constants.h"
#include "AssetLoading/LostConnectionAssetManager.h"

void ALostConnectionPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALostConnectionPlayerState, inventory);

	DOREPLIFETIME(ALostConnectionPlayerState, mainModules);

	DOREPLIFETIME(ALostConnectionPlayerState, weaponModules);

	DOREPLIFETIME(ALostConnectionPlayerState, cooldownableAbilities);

	DOREPLIFETIME(ALostConnectionPlayerState, cooldownableWeapons);

	DOREPLIFETIME(ALostConnectionPlayerState, respawnCooldown);
}

bool ALostConnectionPlayerState::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(inventory, *Bunch, *RepFlags);

	wroteSomething |= inventory->ReplicateSubobjects(Channel, Bunch, RepFlags);

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

	wroteSomething |= Channel->ReplicateSubobject(respawnCooldown, *Bunch, *RepFlags);

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

void ALostConnectionPlayerState::setPrimaryWeapon_Implementation(UBaseWeapon* primaryWeapon)
{
	inventory->setPrimaryWeaponCell(primaryWeapon);
}

void ALostConnectionPlayerState::setSecondaryWeapon_Implementation(UBaseWeapon* secondaryWeapon)
{
	inventory->setPrimaryWeaponCell(secondaryWeapon);
}

void ALostConnectionPlayerState::setFirstInactiveWeapon_Implementation(UBaseWeapon* secondaryWeapon)
{
	// TODO: set inactive weapons
}

void ALostConnectionPlayerState::setSecondInactiveWeapon_Implementation(UBaseWeapon* secondaryWeapon)
{
	// TODO: set inactive weapons
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
	return inventory->getSpareAmmoArray();
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

	inventory = CreateDefaultSubobject<UInventory>("Inventory");
}

void ALostConnectionPlayerState::init()
{
	if (isInitialized)
	{
		return;
	}

	isInitialized = true;

	selectorMaterial = UMaterialInstanceDynamic::Create(ULostConnectionAssetManager::get().getUI().getBaseWeaponSelectorMaterial(), this);

	inventory->init(this);
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
	respawnCooldown->startCooldown();
}

void ALostConnectionPlayerState::increaseLootPoints_Implementation(int32 count)
{
	inventory->setLootPoints(inventory->getLootPoints() + count);
}

void ALostConnectionPlayerState::spendLootPoints_Implementation(int32 count)
{
	inventory->setLootPoints(inventory->getLootPoints() - count);
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

void ALostConnectionPlayerState::setCurrentRespawnCooldown_Implementation(float currentRespawnCooldown)
{
	respawnCooldown->startCooldown(currentRespawnCooldown);
}

UUserWidget* ALostConnectionPlayerState::getCurrentUI() const
{
	return currentUI;
}

UInventory* ALostConnectionPlayerState::getInventory() const
{
	return inventory;
}

const TSubclassOf<ABaseDrone>& ALostConnectionPlayerState::getDroneClass() const
{
	return droneClass;
}

float ALostConnectionPlayerState::getCurrentRespawnCooldown() const
{
	return respawnCooldown->getCurrentCooldown();
}

int32 ALostConnectionPlayerState::getLootPoints() const
{
	return inventory->getLootPoints();
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
