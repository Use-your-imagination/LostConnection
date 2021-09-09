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
#include "Weapons/Pistols/Gauss.h"
#include "WorldPlaceables/DroppedWeapon.h"
#include "Interfaces/PhysicalObjects/ShotThrough.h"
#include "Interfaces/Gameplay/Abilities.h"
#include "Interfaces/Gameplay/MovementActions.h"
#include "Interfaces/Gameplay/AllySelection.h"
#include "Interfaces/Gameplay/Actionable.h"

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

protected:
	/** Camera offset positioning the camera behind the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* CameraOffset;

	/** Follow camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* FollowCamera;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* currentWeaponMesh;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* magazine;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = onRepCurrentWeapon)
	UBaseWeapon* currentWeapon;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, Replicated)
	UBaseWeapon* firstWeaponSlot;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, Replicated)
	UBaseWeapon* secondWeaponSlot;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, Replicated)
	UGauss* defaultWeaponSlot;

private:
	TArray<FInputActionBinding> initInputs();

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

public:
	static FString actionHotkey;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UFUNCTION()
	void onRepCurrentWeapon();

	UFUNCTION(NetMulticast, Reliable)
	void runMulticastReliable(const FName& methodName);

	UFUNCTION(Server, Reliable)
	void runOnServerReliable(const FName& methodName);

	UFUNCTION(NetMulticast, Unreliable)
	void runMulticastUnreliable(const FName& methodName);

	UFUNCTION(Server, Unreliable)
	void runOnServerUnreliable(const FName& methodName);

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
	UFUNCTION()
	void sprint();

	UFUNCTION()
	void run();

	UFUNCTION(NetMulticast, Unreliable)
	void changeMaxSpeed(float speed);

protected:
	UFUNCTION(NetMulticast, Reliable)
	void reloadLogicMulticast();

	UFUNCTION(NetMulticast, Reliable)
	void reloadAnimationMulticast();

	UFUNCTION(BlueprintNativeEvent)
	void reloadAnimation();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void reloadLogic();

	UFUNCTION()
	void shootLogic();

	UFUNCTION()
	void resetShootLogic();

public:
	ALostConnectionCharacter();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void changeToFirstWeapon();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void changeToSecondWeapon();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void changeToDefaultWeapon();

	void updateWeaponMesh();

	UFUNCTION(BlueprintCallable)
	void shoot();

	UFUNCTION(BlueprintCallable)
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

	USkeletalMeshComponent* getCurrentWeaponMesh() const;

	UFUNCTION(BlueprintCallable)
	int getWeaponCount() const;

	UFUNCTION()
	void dropWeapon();

	UFUNCTION()
	void pickupWeapon(ADroppedWeapon* weaponToEquip);

#pragma region Abilities
	UFUNCTION()
	void firstAbility();

	UFUNCTION()
	void secondAbility();

	UFUNCTION()
	void thirdAbility();

	UFUNCTION()
	void ultimateAbility();

	UFUNCTION()
	void releaseFirstAbilityHandle();

	UFUNCTION()
	void releaseSecondAbilityHandle();

	UFUNCTION()
	void releaseThirdAbilityHandle();

	UFUNCTION()
	void releaseUltimateAbilityHandle();
#pragma endregion

#pragma region Selection
	UFUNCTION()
	void selectFirstPlayer();

	UFUNCTION()
	void selectSecondPlayer();

	UFUNCTION()
	void selectThirdPlayer();

	UFUNCTION()
	void selectFourthPlayer();

	UFUNCTION()
	void releaseSelectFirstPlayerHandle();

	UFUNCTION()
	void releaseSelectSecondPlayerHandle();

	UFUNCTION()
	void releaseSelectThirdPlayerHandle();

	UFUNCTION()
	void releaseSelectFourthPlayerHandle();
#pragma endregion

#pragma region PressActions
	UFUNCTION(BlueprintNativeEvent)
	void pressChangeWeapon();

	UFUNCTION(BlueprintNativeEvent)
	void pressAction(AActor* object);

	UFUNCTION(BlueprintNativeEvent)
	void pressAlternative();

	UFUNCTION(BlueprintNativeEvent)
	void pressShoot();

	UFUNCTION(BlueprintNativeEvent)
	void pressDropWeapon();

	UFUNCTION()
	void pressChangeWeaponHandle();

	UFUNCTION()
	void pressActionHandle();

	UFUNCTION()
	void pressAlternativeHandle();
#pragma endregion

#pragma region ReleaseActions
	UFUNCTION(BlueprintNativeEvent)
	void releaseChangeWeapon();

	UFUNCTION(BlueprintNativeEvent)
	void releaseAction();

	UFUNCTION(BlueprintNativeEvent)
	void releaseAlternative();

	UFUNCTION(BlueprintNativeEvent)
	void releaseShoot();

	UFUNCTION(BlueprintNativeEvent)
	void releaseDropWeapon();

	UFUNCTION()
	void releaseChangeWeaponHandle();

	UFUNCTION()
	void releaseActionHandle();

	UFUNCTION()
	void releaseAlternativeHandle();

	UFUNCTION()
	void releaseDropWeaponHandle();
#pragma endregion

	UFUNCTION(BlueprintCallable)
	virtual FVector getStartActionLineTrace() const final;

	UFUNCTION(BlueprintCallable)
	virtual FVector getEndActionLineTrace() const final;

	float getFlatDamageReduction_Implementation() const override;

	float getPercentageDamageReduction_Implementation() const override;

	virtual ~ALostConnectionCharacter() = default;
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
