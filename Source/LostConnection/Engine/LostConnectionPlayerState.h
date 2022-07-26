// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Blueprint/UserWidget.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Weapons/BaseWeapon.h"
#include "Abilities/BaseAbility.h"
#include "Interfaces/Gameplay/Descriptions/Cooldownable.h"
#include "Holders/Utility/CooldownableUtility.h"
#include "Inventory/Inventory.h"
#include "UI/EscapableWidget.h"
#include "Interfaces/Gameplay/Descriptions/DamageAffecter.h"

#include "LostConnectionPlayerState.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API ALostConnectionPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	template<typename T>
	static void reduceCooldownableData(float DeltaSeconds, TArray<T>& cooldownableData);

protected:
	UPROPERTY(Category = UI, BlueprintReadOnly)
	TObjectPtr<UUserWidget> currentUI;

	UPROPERTY(Category = UI, BlueprintReadOnly)
	TObjectPtr<UMaterialInstanceDynamic> selectorMaterial;

	UPROPERTY(Category = Inventory, Replicated, BlueprintReadOnly)
	TObjectPtr<AInventory> inventory;

	UPROPERTY(Category = UI, BlueprintReadOnly)
	TArray<TObjectPtr<UEscapableWidget>> escapableWidgets;

protected:
	UPROPERTY(Replicated)
	TArray<FCooldownableAbilitiesData> cooldownableAbilities;

	UPROPERTY(Replicated)
	TArray<FCooldownableWeaponsData> cooldownableWeapons;

	UPROPERTY(Category = Respawn, Instanced, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	TObjectPtr<UCooldownableUtility> respawnCooldown;

	TArray<TScriptInterface<IDamageAffecter>> damageIncreasers;
	TArray<TScriptInterface<IDamageAffecter>> damageDecreasers;
	TSubclassOf<class ABaseDrone> droneClass;
	bool isInitialized;

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	void BeginPlay() override;

public:
	void onDamageAffecterChange(EDamageAffecterType type);

public:
	ALostConnectionPlayerState();

	UFUNCTION(Server, Reliable)
	void init();

	UFUNCTION(Client, Reliable)
	void resetCurrentUI();

	UFUNCTION(Client, Reliable)
	void createEscapableWidget(TSubclassOf<UEscapableWidget> widgetClass);

	void addEscapableWidget(TObjectPtr<UEscapableWidget> widget);

	void addPersonalModule(UBasePersonalModule* module);

	void addWeaponModule(UBaseWeaponModule* module);

	void addCooldownableAbility(EAbilitySlot slot, const ICooldownable* cooldownable);

	void addCooldownableWeapon(EWeaponSlotType slot, const ICooldownable* cooldownable);

	UFUNCTION(Server, Reliable)
	void returnAmmoToSpare(UBaseWeapon* weapon);
	
	UFUNCTION(Category = EscapeMenu, BlueprintCallable)
	UPARAM(DisplayName = IsEscapableWidgetWasPopped) bool popEscapableWidget();

	UFUNCTION(Server, Reliable)
	void restoreRespawnCooldown();

	UFUNCTION(Server, Reliable)
	void increaseLootPoints(int32 count);

	UFUNCTION(Server, Reliable)
	void spendLootPoints(int32 count);

	void setPrimaryWeapon(UBaseWeapon* weapon);

	void setSecondaryWeapon(UBaseWeapon* weapon);

	void setFirstInactiveWeapon(UBaseWeapon* weapon);

	void setSecondInactiveWeapon(UBaseWeapon* weapon);

	void setMaxSmallAmmoCount(int32 count);

	void setMaxLargeAmmoCount(int32 count);

	void setMaxEnergyAmmoCount(int32 count);

	UFUNCTION(Client, Reliable)
	void setCurrentUI(TSubclassOf<UUserWidget> widget, APawn* outer);

	UFUNCTION(Server, Reliable)
	void setDroneClass(TSubclassOf<class ABaseDrone> newDroneClass);

	UFUNCTION(Server, Reliable)
	void setCurrentRespawnCooldown(float currentRespawnCooldown);

	UFUNCTION(Server, Reliable)
	void setInventory(AInventory* newInventory);

	UBaseWeapon* getPrimaryWeapon() const;

	UBaseWeapon* getSecondaryWeapon() const;

	UBaseWeapon* getDefaultWeapon() const;

	UBaseWeapon* getFirstInactiveWeapon() const;

	UBaseWeapon* getSecondInactiveWeapon() const;

	const TArray<UInventoryCell*>& getPersonalEquippedModules() const;

	const TArray<UInventoryCell*>& getPersonalUnequippedModules() const;

	const TArray<UInventoryCell*>& getWeaponModules() const;

	int32 getSpareAmmo(EAmmoType type) const;

	TArray<FAmmoData>& getSpareAmmoArray();

	const TArray<FCooldownableAbilitiesData>& getCooldownableAbilities() const;

	const TArray<FCooldownableWeaponsData>& getCooldownableWeapons() const;

	int32 getMaxSmallAmmoCount() const;

	int32 getMaxLargeAmmoCount() const;

	int32 getMaxEnergyAmmoCount() const;

	UUserWidget* getCurrentUI() const;

	TObjectPtr<AInventory> getInventory() const;

	const TSubclassOf<class ABaseDrone>& getDroneClass() const;

	float getCurrentRespawnCooldown() const;

	int32 getLootPoints() const;

	TArray<TObjectPtr<UEscapableWidget>>& getEscapableWidgets();

	const TArray<TScriptInterface<IDamageAffecter>>& getDamageIncreasers() const;

	const TArray<TScriptInterface<IDamageAffecter>>& getDamageDecreasers() const;

	TArray<TScriptInterface<IDamageAffecter>> getDamageAffecters() const;

	void Tick(float DeltaSeconds) override;

	~ALostConnectionPlayerState() = default;

#pragma region Multiplayer
private:
	UFUNCTION(NetMulticast, Reliable)
	void runMulticastReliable(AActor* caller, const FName& methodName);

	UFUNCTION(NetMulticast, Unreliable)
	void runMulticastUnreliable(AActor* caller, const FName& methodName);

public:
	UFUNCTION(Server, Reliable)
	void runOnServerReliableWithMulticast(AActor* caller, const FName& methodName);

	UFUNCTION(Server, Unreliable)
	void runOnServerUnreliableWithMulticast(AActor* caller, const FName& methodName);

	UFUNCTION(Server, Reliable)
	void runOnServerReliable(AActor* caller, const FName& methodName);

	UFUNCTION(Server, Unreliable)
	void runOnServerUnreliable(AActor* caller, const FName& methodName);
#pragma endregion
};

inline UBaseWeapon* ALostConnectionPlayerState::getPrimaryWeapon() const
{
	return inventory->getPrimaryWeaponCell()->getItem<UBaseWeapon>();
}

inline UBaseWeapon* ALostConnectionPlayerState::getSecondaryWeapon() const
{
	return inventory->getSecondaryWeaponCell()->getItem<UBaseWeapon>();
}

inline UBaseWeapon* ALostConnectionPlayerState::getDefaultWeapon() const
{
	return inventory->getDefaultWeaponCell()->getItem<UBaseWeapon>();
}

inline UBaseWeapon* ALostConnectionPlayerState::getFirstInactiveWeapon() const
{
	return inventory->getFirstInactiveWeaponCell()->getItem<UBaseWeapon>();
}

inline UBaseWeapon* ALostConnectionPlayerState::getSecondInactiveWeapon() const
{
	return inventory->getSecondInactiveWeaponCell()->getItem<UBaseWeapon>();
}

FORCEINLINE int32 ALostConnectionPlayerState::getSpareAmmo(EAmmoType type) const
{
	for (const FAmmoData& data : inventory->getSpareAmmoArray())
	{
		if (data.ammoType == type)
		{
			return data.ammoCount;
		}
	}

	return 0;
}
