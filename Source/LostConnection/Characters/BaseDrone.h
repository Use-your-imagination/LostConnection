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

#include "BaseDrone.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseDrone :
	public ABaseCharacter,
	public IAbilities,
	public IAllySelection
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

#pragma region Abilities
	UFUNCTION()
	virtual void firstAbility();

	UFUNCTION()
	virtual void secondAbility();

	UFUNCTION()
	virtual void thirdAbility();

	UFUNCTION()
	virtual void ultimateAbility();

	UFUNCTION()
	virtual void releaseFirstAbilityHandle();

	UFUNCTION()
	virtual void releaseSecondAbilityHandle();

	UFUNCTION()
	virtual void releaseThirdAbilityHandle();

	UFUNCTION()
	virtual void releaseUltimateAbilityHandle();
#pragma endregion

#pragma region Selection
	UFUNCTION()
	virtual void selectFirstPlayer();

	UFUNCTION()
	virtual void selectSecondPlayer();

	UFUNCTION()
	virtual void selectThirdPlayer();

	UFUNCTION()
	virtual void selectFourthPlayer();

	UFUNCTION()
	virtual void releaseSelectFirstPlayerHandle();

	UFUNCTION()
	virtual void releaseSelectSecondPlayerHandle();

	UFUNCTION()
	virtual void releaseSelectThirdPlayerHandle();

	UFUNCTION()
	virtual void releaseSelectFourthPlayerHandle();
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
	virtual void pressChangeWeaponHandle();

	UFUNCTION()
	virtual void pressActionHandle();

	UFUNCTION()
	virtual void pressAlternativeHandle();
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
	virtual void releaseChangeWeaponHandle();

	UFUNCTION()
	virtual void releaseActionHandle();

	UFUNCTION()
	virtual void releaseAlternativeHandle();

	UFUNCTION()
	virtual void releaseDropWeaponHandle();
#pragma endregion

	UFUNCTION(BlueprintCallable)
	virtual FVector getStartActionLineTrace() const final;

	UFUNCTION(BlueprintCallable)
	virtual FVector getEndActionLineTrace() const final;

	virtual float getFlatDamageReduction_Implementation() const override;

	virtual float getPercentageDamageReduction_Implementation() const override;

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
