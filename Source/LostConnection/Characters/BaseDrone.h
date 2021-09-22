// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

#include "BaseCharacter.h"
#include "WorldPlaceables/DroppedWeapon.h"
#include "Interfaces/Gameplay/Descriptions/Actionable.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

#include "Abilities/BasePassiveAbility.h"
#include "Abilities/BaseUltimateAbility.h"

#include "BaseDrone.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseDrone :
	public ABaseCharacter,
	public ICaster
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

protected:
	UPROPERTY(Category = CasterStats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float energy;

	UPROPERTY(Category = Abilities, VisibleAnywhere, Replicated, BlueprintReadOnly)
	ABasePassiveAbility* passiveAbility;

	UPROPERTY(Category = Abilities, VisibleAnywhere, Replicated, BlueprintReadOnly)
	ABaseAbility* firstAbility;

	UPROPERTY(Category = Abilities, VisibleAnywhere, Replicated, BlueprintReadOnly)
	ABaseAbility* secondAbility;

	UPROPERTY(Category = Abilities, VisibleAnywhere, Replicated, BlueprintReadOnly)
	ABaseAbility* thirdAbility;

	UPROPERTY(Category = Abilities, VisibleAnywhere, Replicated, BlueprintReadOnly)
	ABaseUltimateAbility* ultimateAbility;

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

	virtual void Tick(float DeltaTime) override;

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

	UFUNCTION()
	virtual void changeWeapon() final;

	UFUNCTION()
	virtual void alternativeWeaponMode() final;

	UFUNCTION()
	virtual void action() final;

	virtual void setEnergy(float newEnergy) final override;

	virtual void setEnergy_Implementation(float newEnergy) final override;

	virtual USpringArmComponent* GetCameraOffset() const final;

	virtual UCameraComponent* GetFollowCamera() const final;

	UFUNCTION(BlueprintCallable)
	virtual int32 getAmmoHoldingCount(ammoTypes type) const final;

	UFUNCTION(BlueprintCallable)
	virtual FVector getStartActionLineTrace() const final;

	UFUNCTION(BlueprintCallable)
	virtual FVector getEndActionLineTrace() const final;

	UFUNCTION(BlueprintNativeEvent)
	void pressShoot();

	UFUNCTION(BlueprintNativeEvent)
	void releaseShoot();

	virtual float getFlatDamageReduction_Implementation() const override;

	virtual float getPercentageDamageReduction_Implementation() const override;

	virtual void usePassiveAbility() final override;

	virtual void useFirstAbility() final override;

	virtual void useSecondAbility() final override;

	virtual void useThirdAbility() final override;

	virtual void useUltimateAbility() final override;

	virtual float getEnergy() const final override;

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
