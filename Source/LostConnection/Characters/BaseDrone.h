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
#include "Interfaces/Gameplay/Actions/InputActions.h"

#include "Interfaces/Gameplay/AnimatedActions/Abilities/PassiveAbilityCast.h"
#include "Interfaces/Gameplay/AnimatedActions/Abilities/FirstAbilityCast.h"
#include "Interfaces/Gameplay/AnimatedActions/Abilities/SecondAbilityCast.h"
#include "Interfaces/Gameplay/AnimatedActions/Abilities/ThirdAbilityCast.h"
#include "Interfaces/Gameplay/AnimatedActions/Abilities/UltimateAbilityCast.h"

#include "BaseDrone.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseDrone :
	public ABaseCharacter,
	public ICaster,
	public IInputActions,
	public IPassiveAbilityCast,
	public IFirstAbilityCast,
	public ISecondAbilityCast,
	public IThirdAbilityCast,
	public IUltimateAbilityCast
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* CameraOffset;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* FollowCamera;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, Replicated)
	ABaseWeapon* firstWeaponSlot;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, Replicated)
	ABaseWeapon* secondWeaponSlot;

private:
	virtual TArray<FInputActionBinding> initInputs();

protected:
	UPROPERTY(Category = CasterStats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float energy;

	UPROPERTY(Category = CasterStats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float currentEnergy;

	UPROPERTY(Category = CasterStats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float energyRestorationPerSecond;

	UPROPERTY(Category = CasterStats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float cooldownReduction;

	UPROPERTY(Category = CasterStats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float duration;

	UPROPERTY(Category = CasterStats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float power;

	UPROPERTY(Category = CasterStats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float energyEfficiency;

	UPROPERTY(Category = CasterStats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float AOE;

	UPROPERTY(Category = CasterStats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float castPoint;

protected:
	UPROPERTY(Category = Abilities, VisibleAnywhere, BlueprintReadOnly)
	ABasePassiveAbility* passiveAbility;

	UPROPERTY(Category = Abilities, VisibleAnywhere, BlueprintReadOnly)
	ABaseAbility* firstAbility;

	UPROPERTY(Category = Abilities, VisibleAnywhere, BlueprintReadOnly)
	ABaseAbility* secondAbility;

	UPROPERTY(Category = Abilities, VisibleAnywhere, BlueprintReadOnly)
	ABaseAbility* thirdAbility;

	UPROPERTY(Category = Abilities, VisibleAnywhere, BlueprintReadOnly)
	ABaseUltimateAbility* ultimateAbility;

#pragma region BlueprintFunctionLibrary
	UPROPERTY(Category = Inputs, VisibleAnywhere, BlueprintReadWrite)
	bool secondaryHold;

	UPROPERTY(Category = Inputs, VisibleAnywhere, BlueprintReadWrite)
	bool weaponSelectorHold;

	UPROPERTY(Category = WeaponSelector, VisibleAnywhere, BlueprintReadWrite)
	int32 selectedWeaponId;

	UPROPERTY(Category = WeaponSelector, VisibleAnywhere, BlueprintReadWrite)
	FVector inputDimensions;

	UPROPERTY(Category = Zoom, VisibleAnywhere, BlueprintReadWrite)
	bool zooming;

	UPROPERTY(Category = Zoom, VisibleAnywhere, BlueprintReadWrite)
	bool zoomBlocked;

	UPROPERTY(Category = Zoom, VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle zoomUpdateHandle;

	UPROPERTY(Category = Wallrun, VisibleAnywhere, BlueprintReadWrite)
	bool wallrun;

	UPROPERTY(Category = Wallrun, VisibleAnywhere, BlueprintReadWrite)
	bool wallrunBlocked;

	UPROPERTY(Category = Wallrun, VisibleAnywhere, BlueprintReadWrite)
	FVector currentWallNormal;

	UPROPERTY(Category = Wallrun, VisibleAnywhere, BlueprintReadWrite)
	FRotator wallrunForward;

	UPROPERTY(Category = Wallrun, VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle wallrunUpdateHandle;

	UPROPERTY(Category = Slide, VisibleAnywhere, BlueprintReadWrite)
	bool isSlideCooldown;

	UPROPERTY(Category = Slide, VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle slideActivityHandle;

	UPROPERTY(Category = Slide, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float slideCooldown;
#pragma endregion

#pragma region BlueprintFunctionLibraryEvents
	UFUNCTION(Category = Zoom, BlueprintNativeEvent, BlueprintCallable)
	void zoomTimerUpdate();

	UFUNCTION(Category = Slide, BlueprintNativeEvent, BlueprintCallable)
	void slideTimerUpdate();

	UFUNCTION(Category = Wallrun, BlueprintNativeEvent, BlueprintCallable)
	void wallrunTimerUpdate();

	UFUNCTION(Category = Wallrun, BlueprintNativeEvent, BlueprintCallable)
	void wallrunCooldown();
#pragma endregion

public:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	float BaseTurnRate;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	float BaseLookUpRate;

public:
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

protected:
	UFUNCTION()
	virtual void pressCrouch() final;

	UFUNCTION()
	virtual void releaseCrouch() final;

	UFUNCTION()
	virtual void pressZoom() final;

	UFUNCTION()
	virtual void releaseZoom() final;

	UFUNCTION()
	virtual void pressWeaponSelector() final;

	UFUNCTION()
	virtual void releaseWeaponSelector() final;

	virtual void deathLogic() override;

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

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void setSlideCooldown(float newSlideCooldown) final;

	virtual USpringArmComponent* GetCameraOffset() const final;

	virtual UCameraComponent* GetFollowCamera() const final;

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

	virtual void setEnergy_Implementation(float newEnergy) final override;

	virtual void setCurrentEnergy_Implementation(float newCurrentEnergy) final override;

	virtual void setEnergyRestorationPerSecond_Implementation(float newEnergyRestorationPerSecond) final override;

	virtual void setCooldownReduction_Implementation(float newCooldownReduction) final override;

	virtual void setDuration_Implementation(float newDuration) final;

	virtual void setPower_Implementation(float newPower) final;
	
	virtual void setEnergyEfficiency_Implementation(float newEnergyEfficiency) final;
	
	virtual void setAOE_Implementation(float newAOE) final;
	
	virtual void setCastPoint_Implementation(float newCastPoint) final;

	UFUNCTION(BlueprintCallable)
	virtual float getEnergy() const final override;

	UFUNCTION(BlueprintCallable)
	virtual float getCurrentEnergy() const final override;

	UFUNCTION(BlueprintCallable)
	virtual float getEnergyRestorationPerSecond() const final override;

	UFUNCTION(BlueprintCallable)
	virtual float getCooldownReduction() const final override;

	UFUNCTION(BlueprintCallable)
	virtual float getDuration() const final;

	UFUNCTION(BlueprintCallable)
	virtual float getPower() const final;

	UFUNCTION(BlueprintCallable)
	virtual float getEnergyEfficiency() const final;

	UFUNCTION(BlueprintCallable)
	virtual float getAOE() const final;

	UFUNCTION(BlueprintCallable)
	virtual float getCastPoint() const final;

	virtual ABasePassiveAbility* getPassiveAbility() final override;

	virtual ABaseAbility* getFirstAbility() final override;

	virtual ABaseAbility* getSecondAbility() final override;

	virtual ABaseAbility* getThirdAbility() final override;

	virtual ABaseUltimateAbility* getUltimateAbility() final override;

#pragma region PassiveAbility
	virtual void castPassiveAbilityVisual() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void castPassiveAbilityLogic() override;
#pragma endregion

#pragma region FirstAbility
	virtual void castFirstAbilityVisual() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void castFirstAbilityLogic() override;
#pragma endregion

#pragma region SecondAbility
	virtual void castSecondAbilityVisual() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void castSecondAbilityLogic() override;
#pragma endregion

#pragma region ThirdAbility
	virtual void castThirdAbilityVisual() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void castThirdAbilityLogic() override;
#pragma endregion

#pragma region UltimateAbility
	virtual void castUltimateAbilityVisual() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void castUltimateAbilityLogic() override;
#pragma endregion

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
