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
#include "Interfaces/Gameplay/Modules/Holders/MainModulesHolder.h"
#include "Interfaces/Gameplay/Modules/Holders/WeaponModulesHolder.h"
#include "Interfaces/Gameplay/Descriptions/Cooldownable.h"
#include "Utility/ReplicationStructures.h"

#include "LostConnectionPlayerState.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API ALostConnectionPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = UI, BlueprintReadOnly)
	UUserWidget* currentUI;

	UPROPERTY(Category = UI, BlueprintReadOnly)
	UMaterialInstanceDynamic* selectorMaterial;

	UPROPERTY(Replicated)
	UBaseWeapon* primaryWeapon;

	UPROPERTY(Replicated)
	UBaseWeapon* secondaryWeapon;

	UPROPERTY(Replicated)
	UBaseWeapon* defaultWeapon;

	UPROPERTY(Replicated)
	UBaseWeapon* firstInactiveWeapon;

	UPROPERTY(Replicated)
	UBaseWeapon* secondInactiveWeapon;

	UPROPERTY(Replicated)
	TArray<UNetworkObject*> mainModules;

	UPROPERTY(Replicated)
	TArray<UNetworkObject*> weaponModules;

	UPROPERTY(Replicated)
	TArray<FAmmoData> spareAmmo;

protected:
	UPROPERTY(Replicated)
	TArray<FCooldownableAbilitiesData> cooldownableAbilities;

	UPROPERTY(Replicated)
	TArray<FCooldownableWeaponsData> cooldownableWeapons;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	virtual void BeginPlay() override;

public:
	void addMainModule(IMainModule* module);

	void addWeaponModule(IWeaponModule* module);

	void addCooldownableAbility(abilitySlot slot, ICooldownable* cooldownable);

	void addCooldownableWeapon(weaponSlotTypes slot, ICooldownable* cooldownable);

	void setPrimaryWeapon(UBaseWeapon* primaryWeapon);

	void setSecondaryWeapon(UBaseWeapon* secondaryWeapon);

	void setDefaultWeapon(UBaseWeapon* defaultWeapon);

	UBaseWeapon* getPrimaryWeapon() const;

	UBaseWeapon* getSecondaryWeapon() const;

	UBaseWeapon* getDefaultWeapon() const;

	UBaseWeapon* getFirstInactiveWeapon() const;

	UBaseWeapon* getSecondInactiveWeapon() const;

	const TArray<UNetworkObject*>& getMainModules() const;

	const TArray<UNetworkObject*>& getWeaponModules() const;

	int32 getSpareAmmo(ammoTypes type) const;

	TArray<FAmmoData>& getSpareAmmoArray();

	const TArray<FCooldownableAbilitiesData>& getCooldownableAbilities() const;

	const TArray<FCooldownableWeaponsData>& getCooldownableWeapons() const;

public:
	ALostConnectionPlayerState();

	void init();

	UFUNCTION(BlueprintCallable)
	UUserWidget* setCurrentUI(UUserWidget* widget);

	UUserWidget* getCurrentUI() const;

	virtual void Tick(float DeltaTime) override;

	virtual ~ALostConnectionPlayerState() = default;
};

inline UBaseWeapon* ALostConnectionPlayerState::getPrimaryWeapon() const
{
	return primaryWeapon;
}

inline UBaseWeapon* ALostConnectionPlayerState::getSecondaryWeapon() const
{
	return secondaryWeapon;
}

inline UBaseWeapon* ALostConnectionPlayerState::getDefaultWeapon() const
{
	return defaultWeapon;
}

inline UBaseWeapon* ALostConnectionPlayerState::getFirstInactiveWeapon() const
{
	return firstInactiveWeapon;
}

inline UBaseWeapon* ALostConnectionPlayerState::getSecondInactiveWeapon() const
{
	return secondInactiveWeapon;
}

inline int32 ALostConnectionPlayerState::getSpareAmmo(ammoTypes type) const
{
	for (const auto& data : spareAmmo)
	{
		if (data.ammoType == type)
		{
			return data.ammoCount;
		}
	}

	return 0;
}
