// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionPlayerState.h"

#include "Constants/Constants.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "LostConnectionPlayerController.h"
#include "Utility/Utility.h"

template<typename T>
void ALostConnectionPlayerState::reduceCooldownableData(float DeltaTime, TArray<T>& cooldownableData)
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

	DOREPLIFETIME(ALostConnectionPlayerState, inventory);

	DOREPLIFETIME(ALostConnectionPlayerState, playerController);

	DOREPLIFETIME(ALostConnectionPlayerState, cooldownableAbilities);

	DOREPLIFETIME(ALostConnectionPlayerState, cooldownableWeapons);

	DOREPLIFETIME(ALostConnectionPlayerState, respawnCooldown);
}

bool ALostConnectionPlayerState::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(respawnCooldown, *Bunch, *RepFlags);

	return wroteSomething;
}

void ALostConnectionPlayerState::addPersonalModule(UBasePersonalModule* module)
{
	inventory->addPersonalModule(module);
}

void ALostConnectionPlayerState::addWeaponModule(UBaseWeaponModule* module)
{
	inventory->addWeaponModule(module);
}

void ALostConnectionPlayerState::addCooldownableAbility(EAbilitySlot slot, const ICooldownable* cooldownable)
{
	if (!cooldownable->isUsable())
	{
		cooldownableAbilities.Add(FCooldownableAbilitiesData(slot, cooldownable->getCurrentCooldown()));
	}
}

void ALostConnectionPlayerState::addCooldownableWeapon(EWeaponSlotType slot, const ICooldownable* cooldownable)
{
	if (!cooldownable->isUsable())
	{
		cooldownableWeapons.Add(FCooldownableWeaponsData(slot, cooldownable->getCurrentCooldown()));
	}
}

void ALostConnectionPlayerState::returnAmmoToSpare_Implementation(UBaseWeapon* weapon)
{
	if (!weapon)
	{
		return;
	}

	EAmmoType ammoType = weapon->getAmmoType();

	if (ammoType == EAmmoType::defaultType)
	{
		return;
	}

	TArray<FAmmoData>& spareAmmo = this->getSpareAmmoArray();
	int32& currentWeaponSpareAmmo = Algo::FindByPredicate(spareAmmo, [&ammoType](FAmmoData& data) { return data.ammoType == ammoType; })->ammoCount;
	int32 maxCount = 0;

	switch (ammoType)
	{
	case EAmmoType::small:
		maxCount = this->getMaxSmallAmmoCount();

		break;

	case EAmmoType::large:
		maxCount = this->getMaxLargeAmmoCount();

		break;

	case EAmmoType::energy:
		maxCount = this->getMaxEnergyAmmoCount();

		break;
	}

	int32 tem = FMath::Min(maxCount, currentWeaponSpareAmmo + weapon->getCurrentMagazineSize());

	if (tem == maxCount)
	{
		weapon->setCurrentMagazineSize(currentWeaponSpareAmmo + weapon->getCurrentMagazineSize() - maxCount);
	}
	else
	{
		weapon->setCurrentMagazineSize(0);
	}

	currentWeaponSpareAmmo = tem;
}

void ALostConnectionPlayerState::setPrimaryWeapon(UBaseWeapon* weapon)
{
	inventory->setPrimaryWeaponCell(weapon);
}

void ALostConnectionPlayerState::setSecondaryWeapon(UBaseWeapon* weapon)
{
	inventory->setPrimaryWeaponCell(weapon);
}

void ALostConnectionPlayerState::setFirstInactiveWeapon(UBaseWeapon* weapon)
{
	inventory->setFirstInactiveWeaponCell(weapon);
}

void ALostConnectionPlayerState::setSecondInactiveWeapon(UBaseWeapon* weapon)
{
	inventory->setSecondInactiveWeaponCell(weapon);
}

void ALostConnectionPlayerState::setMaxSmallAmmoCount(int32 count)
{
	inventory->setMaxSmallAmmoCount(count);
}

void ALostConnectionPlayerState::setMaxLargeAmmoCount(int32 count)
{
	inventory->setMaxLargeAmmoCount(count);
}

void ALostConnectionPlayerState::setMaxEnergyAmmoCount(int32 count)
{
	inventory->setMaxEnergyAmmoCount(count);
}

void ALostConnectionPlayerState::setPlayerController_Implementation(ALostConnectionPlayerController* newPlayerController)
{
	playerController = newPlayerController;
}

const TArray<UInventoryCell*>& ALostConnectionPlayerState::getPersonalEquippedModules() const
{
	return inventory->getPersonalEquippedModules();
}

const TArray<UInventoryCell*>& ALostConnectionPlayerState::getPersonalUnequippedModules() const
{
	return inventory->getPersonalUnequippedModules();
}

const TArray<UInventoryCell*>& ALostConnectionPlayerState::getWeaponModules() const
{
	return inventory->getWeaponModules();
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

int32 ALostConnectionPlayerState::getMaxSmallAmmoCount() const
{
	return inventory->getMaxSmallAmmoCount();
}

int32 ALostConnectionPlayerState::getMaxLargeAmmoCount() const
{
	return inventory->getMaxLargeAmmoCount();
}

int32 ALostConnectionPlayerState::getMaxEnergyAmmoCount() const
{
	return inventory->getMaxEnergyAmmoCount();
}

ALostConnectionPlayerController* ALostConnectionPlayerState::getPlayerController() const
{
	return playerController;
}

void ALostConnectionPlayerState::BeginPlay()
{
	Super::BeginPlay();

	selectorMaterial = UMaterialInstanceDynamic::Create(ULostConnectionAssetManager::get().getUI().getBaseWeaponSelectorMaterial(), this);

	if (HasAuthority())
	{
		inventory = GetWorld()->SpawnActor<AInventory>();
		
		inventory->init(this);
	}
}

ALostConnectionPlayerState::ALostConnectionPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
}

void ALostConnectionPlayerState::init_Implementation()
{
	inventory->SetOwner(playerController);
}

void ALostConnectionPlayerState::resetCurrentUI_Implementation()
{
	if (IsValid(currentUI))
	{
		currentUI->RemoveFromViewport();
	}

	currentUI = nullptr;
}

void ALostConnectionPlayerState::createEscapableWidget_Implementation(TSubclassOf<UEscapableWidget> widgetClass)
{
	UEscapableWidget* widget = CreateWidget<UEscapableWidget>(playerController, widgetClass);

	widget->init(this);

	this->addEscapableWidget(widget);
}

void ALostConnectionPlayerState::addEscapableWidget(UEscapableWidget* widget)
{
	int32 nextZOrder = escapableWidgets.Num() ? escapableWidgets.Last()->getZOrder() + 1 : UConstants::startZOrder;

	widget->setZOrder(nextZOrder);

	for (UEscapableWidget* previousWidget : escapableWidgets)
	{
		previousWidget->updateAsPrevious(widget->getIsPreviousVisible(), widget->getIsPreviousHitTestable());
	}

	escapableWidgets.Add_GetRef(widget)->updateAsTop();

	escapableWidgets.Last()->AddToViewport(nextZOrder);
}

bool ALostConnectionPlayerState::popEscapableWidget()
{
	if (!escapableWidgets.Num())
	{
		return false;
	}

	escapableWidgets.Last()->RemoveFromViewport();

	escapableWidgets.Pop();

	if (!escapableWidgets.Num())
	{
		this->getCurrentUI()->SetVisibility(ESlateVisibility::Visible);

		playerController->SetInputMode(FInputModeGameOnly());

		playerController->SetShowMouseCursor(false);

		return true;
	}

	UEscapableWidget*& widget = escapableWidgets.Last();

	for (UEscapableWidget* previousWidget : escapableWidgets)
	{
		if (previousWidget == widget)
		{
			widget->updateAsTop();

			break;
		}

		previousWidget->updateAsPrevious(widget->getIsPreviousVisible(), widget->getIsPreviousHitTestable());
	}

	return true;
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

TObjectPtr<AInventory> ALostConnectionPlayerState::getInventory() const
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

TArray<UEscapableWidget*>& ALostConnectionPlayerState::getEscapableWidgets()
{
	return escapableWidgets;
}

void ALostConnectionPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		ALostConnectionPlayerState::reduceCooldownableData(DeltaTime, cooldownableAbilities);

		ALostConnectionPlayerState::reduceCooldownableData(DeltaTime, cooldownableWeapons);

		respawnCooldown->processCooldown(DeltaTime);
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
