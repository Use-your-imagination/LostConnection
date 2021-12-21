// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Blueprint/UserWidget.h"

#include "Weapons/BaseWeapon.h"
#include "Interfaces/Gameplay/Modules/Holders/MainModulesHolder.h"
#include "Interfaces/Gameplay/Modules/Holders/WeaponModulesHolder.h"

#include "LostConnectionPlayerState.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API ALostConnectionPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = UI, BlueprintReadOnly)
	UUserWidget* currentUI;

	UPROPERTY(Replicated)
	UBaseWeapon* primaryWeapon;

	UPROPERTY(Replicated)
	UBaseWeapon* secondaryWeapon;

	UPROPERTY(Replicated)
	UBaseWeapon* defaultWeapon;

	UPROPERTY(Replicated)
	TArray<UObject*> mainModules;

	UPROPERTY(Replicated)
	TArray<UObject*> weaponModules;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

public:
	virtual void addMainModule(IMainModule* module) final;

	virtual void addWeaponModule(IWeaponModule* module) final;

	virtual void setPrimaryWeapon(UBaseWeapon* primaryWeapon) final;

	virtual void setSecondaryWeapon(UBaseWeapon* secondaryWeapon) final;

	virtual void setDefaultWeapon(UBaseWeapon* defaultWeapon) final;

	virtual UBaseWeapon* getPrimaryWeapon() const final;

	virtual UBaseWeapon* getSecondaryWeapon() const final;

	virtual UBaseWeapon* getDefaultWeapon() const final;

	virtual const TArray<UObject*>& getMainModules() const final;

	virtual const TArray<UObject*>& getWeaponModules() const final;

public:
	ALostConnectionPlayerState();

	UFUNCTION(BlueprintCallable)
	virtual UUserWidget* setCurrentUI(UUserWidget* widget) final;

	virtual UUserWidget* getCurrentUI() const final;

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
