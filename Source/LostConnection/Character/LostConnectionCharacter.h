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
#include "Interfaces/ShotThrough.h"

#include "LostConnectionCharacter.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionCharacter :
	public ACharacter,
	public IShotThrough
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

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, Replicated, BlueprintReadOnly)
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
	void sprint();

	void run();

public:
	ALostConnectionCharacter();

	void changeToFirstWeapon();

	UFUNCTION(Server, Reliable)
	void clientChangeToFirstWeapon();

	void changeToSecondWeapon();

	UFUNCTION(Server, Reliable)
	void clientChangeToSecondWeapon();

	UFUNCTION(BlueprintCallable)
	void changeToDefaultWeapon();

	UFUNCTION(Server, Reliable)
	void clientChangeToDefaultWeapon();

	void updateWeaponMesh();

	UFUNCTION(BlueprintCallable)
	void shoot();

	UFUNCTION(Server, Reliable)
	void clientShoot();

	UFUNCTION(BlueprintCallable)
	void resetShoot();

	UFUNCTION(Server, Reliable)
	void clientResetShoot();

	void reload();

	void restoreHealth(float amount);

	void takeDamage(float amount);

	UFUNCTION(BlueprintCallable)
	void pickupAmmo(ammoTypes type, int32 count);

	UFUNCTION(Server, Reliable)
	void setCurrentHealth(int newCurrentHealth);

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

	USkeletalMeshComponent* getCurrentWeaponMesh() const;

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
