// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Net/DataBunch.h"

#include "Weapons/BaseWeapon.h"
#include "WorldPlaceables/DroppedWeapon.h"
#include "Interfaces/PhysicalObjects/ShotThrough.h"
#include "Interfaces/Gameplay/AnimatedActions/Reload.h"
#include "Interfaces/Gameplay/AnimatedActions/Shoot.h"

#include "BaseCharacter.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseCharacter :
	public ACharacter,
	public IShotThrough,
	public IReload,
	public IShoot
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* currentWeaponMesh;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* magazine;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = onCurrentWeaponChange)
	UBaseWeapon* currentWeapon;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, Replicated)
	UBaseWeapon* defaultWeaponSlot;

protected:
	UPROPERTY(Category = Stats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float health;

	UPROPERTY(Category = Stats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float currentHealth;

	UPROPERTY(Category = Properties, VisibleAnywhere, Replicated, BlueprintReadWrite)
	bool isAlly;

private:
	UFUNCTION()
	void onCurrentWeaponChange();

	void updateWeaponMesh();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

protected:
	UFUNCTION()
	virtual void sprint();

	UFUNCTION()
	virtual void run();

	UFUNCTION(NetMulticast, Reliable)
	void setMaxSpeed(float speed);

#pragma region Reload
protected:
	virtual void reloadVisual() override;

	virtual void reloadLogic() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void runReloadLogic() final;

#pragma endregion

#pragma region Shoot
protected:
	virtual void shootVisual() override;

	virtual void shootLogic() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void runShootLogic() final;
#pragma endregion

public:	
	ABaseCharacter();

	virtual ~ABaseCharacter() = default;
};
