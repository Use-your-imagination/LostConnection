// Copyright (c) 2021 Use-your-imagination

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
#include "Utility/CooldownableUtility.h"
#include "Inventory/Inventory.h"

#include "LostConnectionPlayerState.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API ALostConnectionPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	template<typename T>
	static void reduceCooldownableData(float DeltaTime, TArray<T>& cooldownableData);

protected:
	UPROPERTY(Category = UI, BlueprintReadOnly)
	UUserWidget* currentUI;

	UPROPERTY(Category = UI, BlueprintReadOnly)
	UMaterialInstanceDynamic* selectorMaterial;

	UPROPERTY(Category = Inventory, Replicated, BlueprintReadOnly)
	UInventory* inventory;

protected:
	UPROPERTY(Replicated)
	TArray<FCooldownableAbilitiesData> cooldownableAbilities;

	UPROPERTY(Replicated)
	TArray<FCooldownableWeaponsData> cooldownableWeapons;

	UPROPERTY(Category = Respawn, Instanced, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UCooldownableUtility* respawnCooldown;

	TSubclassOf<class ABaseDrone> droneClass;

	bool isInitialized;

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

public:
	UFUNCTION(Server, Reliable)
	void addPersonalModule(UBasePersonalModule* module);

	UFUNCTION(Server, Reliable)
	void addWeaponModule(UBaseWeaponModule* module);

	void addCooldownableAbility(EAbilitySlot slot, const ICooldownable* cooldownable);

	void addCooldownableWeapon(EWeaponSlotType slot, const ICooldownable* cooldownable);

	UFUNCTION(Server, Reliable)
	void setPrimaryWeapon(UBaseWeapon* weapon);

	UFUNCTION(Server, Reliable)
	void setSecondaryWeapon(UBaseWeapon* weapon);

	UFUNCTION(Server, Reliable)
	void setFirstInactiveWeapon(UBaseWeapon* weapon);

	UFUNCTION(Server, Reliable)
	void setSecondInactiveWeapon(UBaseWeapon* weapon);

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

public:
	ALostConnectionPlayerState();

	void init();

	UFUNCTION(Client, Reliable)
	void resetCurrentUI();

	UFUNCTION(Server, Reliable)
	void restoreRespawnCooldown();

	UFUNCTION(Server, Reliable)
	void increaseLootPoints(int32 count);

	UFUNCTION(Server, Reliable)
	void spendLootPoints(int32 count);

	UFUNCTION(Client, Reliable)
	void setCurrentUI(TSubclassOf<UUserWidget> widget, APawn* outer);

	UFUNCTION(Server, Reliable)
	void setDroneClass(TSubclassOf<class ABaseDrone> newDroneClass);

	UFUNCTION(Server, Reliable)
	void setCurrentRespawnCooldown(float currentRespawnCooldown);

	UUserWidget* getCurrentUI() const;

	UInventory* getInventory() const;

	const TSubclassOf<class ABaseDrone>& getDroneClass() const;

	float getCurrentRespawnCooldown() const;

	int32 getLootPoints() const;

	virtual void Tick(float DeltaTime) override;

	virtual ~ALostConnectionPlayerState() = default;

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
	TArray<FAmmoData>& spareAmmo = inventory->getSpareAmmoArray();

	for (const auto& data : spareAmmo)
	{
		if (data.ammoType == type)
		{
			return data.ammoCount;
		}
	}

	return 0;
}
