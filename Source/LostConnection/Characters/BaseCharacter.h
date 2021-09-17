// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Net/DataBunch.h"

#include "Weapons/BaseWeapon.h"
#include "WorldPlaceables/DroppedWeapon.h"
#include "Interfaces/PhysicalObjects/ShotThrough.h"

#include "BaseCharacter.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseCharacter :
	public ACharacter,
	public IShotThrough
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* CameraOffset;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* FollowCamera;

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
	void sprint();

	UFUNCTION()
	void run();

	UFUNCTION(NetMulticast, Reliable)
	void setMaxSpeed(float speed);

protected:
	UFUNCTION()
	void reloadImplementation();

	UFUNCTION(BlueprintNativeEvent)
	void playReloadAnimation();

public:	
	ABaseCharacter();

	UFUNCTION()
	void reload();

	virtual ~ABaseCharacter() = default;
};
