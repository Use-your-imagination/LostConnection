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
#include "Interfaces/Modules/Holders/PersonalModulesHolder.h"
#include "Interfaces/Modules/Holders/WeaponModulesHolder.h"
#include "Interfaces/Gameplay/Descriptions/Cooldownable.h"
#include "Utility/CooldownableUtilityObject.h"
#include "Inventory/Inventory.h"

#include "LostConnectionPlayerState.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API ALostConnectionPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	template<typename T>
	static void reduceCooldownableDataObjects(float DeltaTime, TArray<T>& cooldownableData);

protected:
	UPROPERTY(Category = UI, BlueprintReadOnly)
	UUserWidget* currentUI;

	UPROPERTY(Category = UI, BlueprintReadOnly)
	UMaterialInstanceDynamic* selectorMaterial;

	UPROPERTY(Category = Inventory, Replicated, BlueprintReadOnly)
	UInventory* inventory;

	UPROPERTY(Replicated)
	TArray<UBasePersonalModule*> personalModules;

	UPROPERTY(Replicated)
	TArray<UBaseWeaponModule*> weaponModules;

protected:
	UPROPERTY(Replicated)
	TArray<FCooldownableAbilitiesData> cooldownableAbilities;

	UPROPERTY(Replicated)
	TArray<FCooldownableWeaponsData> cooldownableWeapons;

	UPROPERTY(Category = Respawn, Instanced, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UCooldownableUtilityObject* respawnCooldown;

	TSubclassOf<class ABaseDrone> droneClass;

	bool isInitialized;

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

public:
	void addPersonalModule(UBasePersonalModule* module);

	void addWeaponModule(UBaseWeaponModule* module);

	void addCooldownableAbility(abilitySlot slot, const ICooldownable* cooldownable);

	void addCooldownableWeapon(weaponSlotTypes slot, const ICooldownable* cooldownable);

	UFUNCTION(Server, Reliable)
	void setPrimaryWeapon(UBaseWeapon* primaryWeapon);

	UFUNCTION(Server, Reliable)
	void setSecondaryWeapon(UBaseWeapon* secondaryWeapon);

	UFUNCTION(Server, Reliable)
	void setFirstInactiveWeapon(UBaseWeapon* secondaryWeapon);

	UFUNCTION(Server, Reliable)
	void setSecondInactiveWeapon(UBaseWeapon* secondaryWeapon);

	UBaseWeapon* getPrimaryWeapon() const;

	UBaseWeapon* getSecondaryWeapon() const;

	UBaseWeapon* getDefaultWeapon() const;

	UBaseWeapon* getFirstInactiveWeapon() const;

	UBaseWeapon* getSecondInactiveWeapon() const;

	const TArray<UBasePersonalModule*>& getPersonalModules() const;

	const TArray<UBaseWeaponModule*>& getWeaponModules() const;

	int32 getSpareAmmo(ammoTypes type) const;

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

template<typename T>
void ALostConnectionPlayerState::reduceCooldownableDataObjects(float DeltaTime, TArray<T>& cooldownableData)
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
	// TODO: inactive weapon getter

	return nullptr;
}

inline UBaseWeapon* ALostConnectionPlayerState::getSecondInactiveWeapon() const
{
	// TODO: inactive weapon getter

	return nullptr;
}

FORCEINLINE int32 ALostConnectionPlayerState::getSpareAmmo(ammoTypes type) const
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

FORCEINLINE void ALostConnectionPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		ALostConnectionPlayerState::reduceCooldownableDataObjects(DeltaTime, cooldownableAbilities);

		ALostConnectionPlayerState::reduceCooldownableDataObjects(DeltaTime, cooldownableWeapons);

		respawnCooldown->processCooldown(DeltaTime);
	}
}
