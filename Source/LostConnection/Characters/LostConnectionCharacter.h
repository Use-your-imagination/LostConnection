// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

#include "BaseCharacter.h"
#include "WorldPlaceables/DroppedWeapon.h"
#include "Interfaces/Gameplay/Abilities.h"
#include "Interfaces/Gameplay/AllySelection.h"
#include "Interfaces/Gameplay/Actionable.h"

#include "LostConnectionCharacter.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionCharacter :
	public ABaseCharacter,
	public IAbilities,
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
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	float BaseLookUpRate;

public:
	static FString actionHotkey;

	static ALostConnectionCharacter* globalPlayerPtr;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

protected:
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void reloadLogic() override;

public:
	ALostConnectionCharacter();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void changeToFirstWeapon();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void changeToSecondWeapon();

	UFUNCTION(BlueprintCallable)
	void pickupAmmo(ammoTypes type, int32 count);

	UFUNCTION()
	void dropWeapon();

	UFUNCTION(Server, Reliable)
	void pickupWeapon(ADroppedWeapon* weaponToEquip);

	/** Returns CameraOffset subobject **/
	USpringArmComponent* GetCameraOffset() const;

	/** Returns FollowCamera subobject **/
	UCameraComponent* GetFollowCamera() const;

	UFUNCTION(BlueprintCallable)
	int32 getAmmoHoldingCount(ammoTypes type) const;

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

	virtual float getFlatDamageReduction_Implementation() const override;

	virtual float getPercentageDamageReduction_Implementation() const override;

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
