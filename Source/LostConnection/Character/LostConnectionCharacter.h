// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Net/DataBunch.h"

#include "BaseEntities/BaseWeapon.h"
#include "Weapons/DefaultWeapon.h"
#include "Interfaces/PhysicalObjects/ShotThrough.h"
#include "Interfaces/Gameplay/Abilities.h"
#include "Interfaces/Gameplay/MovementActions.h"
#include "Interfaces/Gameplay/AllySelection.h"

#include "LostConnectionCharacter.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionCharacter :
	public ACharacter,
	public IShotThrough,
	public IAbilities,
	public IMovementActions,
	public IAllySelection
{
	GENERATED_BODY()

	/** Camera offset positioning the camera behind the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraOffset;

	/** Follow camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* currentWeaponMesh;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* magazine;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = onRepCurrentWeapon, meta = (AllowPrivateAccess = "true"))
	UBaseWeapon* currentWeapon;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, Replicated, meta = (AllowPrivateAccess = "true"))
	UBaseWeapon* firstWeaponSlot;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, Replicated, meta = (AllowPrivateAccess = "true"))
	UBaseWeapon* secondWeaponSlot;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, Replicated, meta = (AllowPrivateAccess = "true"))
	UDefaultWeapon* defaultWeaponSlot;

private:
	TArray<FInputActionBinding> initInterfaceInputs();

private:
	FTimerHandle shootHandle;

	float shootRemainingTime;

	bool clearTimer;

protected:
	UPROPERTY(Category = Stats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float health;

	UPROPERTY(Category = Stats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float currentHealth;

	UPROPERTY(Category = Properties, VisibleAnywhere, Replicated, BlueprintReadWrite)
	bool isAlly;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadOnly)
	TArray<int32> currentAmmoHolding;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	float BaseLookUpRate;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UFUNCTION()
	void onRepCurrentWeapon();

protected:
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

private:
	virtual void Jump() final override;

	virtual void StopJumping() final override;

private:
	UFUNCTION(Server, Unreliable)
	void sprint();

	UFUNCTION(Server, Unreliable)
	void run();

	UFUNCTION(NetMulticast, Unreliable)
	void changeMaxSpeed(float speed);

	UFUNCTION(NetMulticast, Reliable)
	void reloadAnimationMulticast();

protected:
	UFUNCTION(BlueprintNativeEvent)
	void pressAlternative();

	UFUNCTION(BlueprintNativeEvent)
	void releaseAlternative();

	UFUNCTION(BlueprintNativeEvent)
	void pressShoot();

	UFUNCTION(BlueprintNativeEvent)
	void releaseShoot();

protected:
	void reloadGameplay();

	UFUNCTION(BlueprintNativeEvent)
	void reloadAnimation();

public:
	ALostConnectionCharacter();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void changeToFirstWeapon();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void changeToSecondWeapon();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void changeToDefaultWeapon();

	void updateWeaponMesh();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void shoot();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void resetShoot();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void reload();

	void restoreHealth(float amount);

	void takeDamage(float amount);

	UFUNCTION(BlueprintCallable)
	void pickupAmmo(ammoTypes type, int32 count);

	UFUNCTION(Server, Reliable)
	void setCurrentHealth(int newCurrentHealth);

	UFUNCTION(Server, Reliable)
	void setIsAlly(bool newIsAlly);

	/** Returns CameraOffset subobject **/
	USpringArmComponent* GetCameraOffset() const;

	/** Returns FollowCamera subobject **/
	UCameraComponent* GetFollowCamera() const;

	UFUNCTION(BlueprintCallable)
	float getHealth() const;

	UFUNCTION(BlueprintCallable)
	float getCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	bool getIsAlly() const;

	UFUNCTION(BlueprintCallable)
	int32 getAmmoHoldingCount(ammoTypes type) const;

	UFUNCTION(BlueprintCallable)
	bool isWeaponEquipped() const;

	UFUNCTION(Server, Reliable)
	void firstAbility();

	UFUNCTION(Server, Reliable)
	void secondAbility();

	UFUNCTION(Server, Reliable)
	void thirdAbility();

	UFUNCTION(Server, Reliable)
	void ultimateAbility();

	UFUNCTION(Server, Reliable)
	void selectFirstPlayer();

	UFUNCTION(Server, Reliable)
	void selectSecondPlayer();

	UFUNCTION(Server, Reliable)
	void selectThirdPlayer();

	UFUNCTION(Server, Reliable)
	void selectFourthPlayer();

	UFUNCTION(BlueprintNativeEvent)
	void pressChangeWeapon();

	UFUNCTION(BlueprintNativeEvent)
	void releaseChangeWeapon();

	UFUNCTION(BlueprintNativeEvent)
	void pressAction();

	UFUNCTION(BlueprintNativeEvent)
	void releaseAction();

	USkeletalMeshComponent* getCurrentWeaponMesh() const;

	UFUNCTION(BlueprintCallable)
	int getWeaponCount() const;

	float getFlatDamageReduction_Implementation() const override;

	float getPercentageDamageReduction_Implementation() const override;

	~ALostConnectionCharacter() = default;
};

inline USpringArmComponent* ALostConnectionCharacter::GetCameraOffset() const
{
	return CameraOffset;
}

inline UCameraComponent* ALostConnectionCharacter::GetFollowCamera() const
{
	return FollowCamera;
}

inline bool ALostConnectionCharacter::isWeaponEquipped() const
{
	return static_cast<bool>(currentWeapon);
}
