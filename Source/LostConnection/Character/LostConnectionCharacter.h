// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
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

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ABaseWeapon* currentWeapon;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ABaseWeapon* firstWeaponSlot;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ABaseWeapon* secondWeaponSlot;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ADefaultWeapon* defaultWeaponSlot;

private:
	FTimerHandle shootHandle;

	float shootRemainingTime;

	bool clearTimer;

protected:
	UPROPERTY(Category = Stats, VisibleAnywhere, BlueprintReadOnly)
	float healths;

	UPROPERTY(Category = Stats, VisibleAnywhere, BlueprintReadOnly)
	float currentHealths;

	UPROPERTY(Category = Properties, VisibleAnywhere, BlueprintReadWrite)
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

	void changeToSecondWeapon();

	UFUNCTION(BlueprintCallable)
	void changeToDefaultWeapon();

	void updateWeaponMesh();

	UFUNCTION(BlueprintCallable)
	void shoot();

	UFUNCTION(BlueprintCallable)
	void resetShoot();

	void reload();

	void restoreHealths(float amount);

	void takeDamage(float amount);

	UFUNCTION(BlueprintCallable)
	void pickupAmmo(ammoTypes type, int32 count);

	void setCurrentHealths(int currentHealths);

	/** Returns CameraOffset subobject **/
	USpringArmComponent* GetCameraOffset() const;

	/** Returns FollowCamera subobject **/
	UCameraComponent* GetFollowCamera() const;

	UFUNCTION(BlueprintCallable)
	float getHealths() const;

	UFUNCTION(BlueprintCallable)
	float getCurrentHealths() const;

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
