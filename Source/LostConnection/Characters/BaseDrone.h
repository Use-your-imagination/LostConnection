// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

#include "BaseCharacter.h"
#include "WorldPlaceables/DroppedWeapon.h"
#include "Interfaces/Gameplay/Actionable.h"

#include "BaseDrone.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseDrone :
	public ABaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* CameraOffset;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* FollowCamera;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, Replicated)
	UBaseWeapon* firstWeaponSlot;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, Replicated)
	UBaseWeapon* secondWeaponSlot;

private:
	TArray<FInputActionBinding> initInputs();

protected:
	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, Replicated, BlueprintReadOnly)
	TArray<int32> currentAmmoHolding;

public:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	float BaseTurnRate;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	float BaseLookUpRate;

public:
	static FString actionHotkey;

	static ABaseDrone* globalPlayerPtr;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void MoveForward(float Value) final;

	virtual void MoveRight(float Value) final;

	virtual void TurnAtRate(float Rate) final;

	virtual void LookUpAtRate(float Rate) final;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void reloadLogic() override final;

public:
	ABaseDrone();

	virtual void shoot() final override;

	virtual void resetShoot() final override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void changeToFirstWeapon() final;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void changeToSecondWeapon() final;

	UFUNCTION(BlueprintCallable)
	virtual void pickupAmmo(ammoTypes type, int32 count) final;

	UFUNCTION()
	virtual void dropWeapon() final;

	UFUNCTION(Server, Reliable)
	virtual void pickupWeapon(ADroppedWeapon* weaponToEquip) final;

	virtual USpringArmComponent* GetCameraOffset() const final;

	virtual UCameraComponent* GetFollowCamera() const final;

	UFUNCTION(BlueprintCallable)
	virtual int32 getAmmoHoldingCount(ammoTypes type) const final;

	UFUNCTION()
	virtual void changeWeapon() final;

	UFUNCTION()
	virtual void alternativeWeaponMode() final;

	UFUNCTION()
	virtual void action() final;

	UFUNCTION(BlueprintCallable)
	virtual FVector getStartActionLineTrace() const final;

	UFUNCTION(BlueprintCallable)
	virtual FVector getEndActionLineTrace() const final;

	virtual float getFlatDamageReduction_Implementation() const override;

	virtual float getPercentageDamageReduction_Implementation() const override;

	UFUNCTION(BlueprintNativeEvent)
	void pressShoot();

	UFUNCTION(BlueprintNativeEvent)
	void releaseShoot();

	virtual ~ABaseDrone() = default;
};

inline USpringArmComponent* ABaseDrone::GetCameraOffset() const
{
	return CameraOffset;
}

inline UCameraComponent* ABaseDrone::GetFollowCamera() const
{
	return FollowCamera;
}
