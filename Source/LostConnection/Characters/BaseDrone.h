// Copyright (c) 2021 Use Your Imagination

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
#include "Constants/Constants.h"
#include "Grapple/BaseGrappleHandler.h"

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
	public IPassiveAbilityCast,
	public IFirstAbilityCast,
	public ISecondAbilityCast,
	public IThirdAbilityCast,
	public IUltimateAbilityCast,
	public IInputActions,
	public IPersonalModulesHolder,
	public IWeaponModulesHolder
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> CameraOffset;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> FollowCamera;

private:
	virtual TArray<FInputActionBinding> initInputs();

protected:
	UPROPERTY(Category = CharacterInformation, EditDefaultsOnly, BlueprintReadOnly)
	FText droneMK;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float energy;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float currentEnergy;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float energyRestorationPerSecond;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float cooldownReduction;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float duration;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float power;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float energyEfficiency;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float AOE;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float castPoint;

protected:
	UPROPERTY(Category = Abilities, ReplicatedUsing = onAbilityUsed, BlueprintReadOnly)
	EAbilitySlot abilityId;

	UPROPERTY(Category = Abilities, BlueprintReadOnly)
	TObjectPtr<UBaseAbility> currentAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	TObjectPtr<UBasePassiveAbility> passiveAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	TObjectPtr<UBaseAbility> firstAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	TObjectPtr<UBaseAbility> secondAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	TObjectPtr<UBaseAbility> thirdAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	TObjectPtr<UBaseUltimateAbility> ultimateAbility;

	UPROPERTY(Category = Animations, EditDefaultsOnly, BlueprintReadOnly)
	TArray<TObjectPtr<UAnimMontage>> abilitiesAnimations;

	UPROPERTY(Category = Death, EditDefaultsOnly, BlueprintReadOnly)
	bool isFullyDestruction;

	UPROPERTY(Category = Grapple, Replicated, BlueprintReadOnly)
	TObjectPtr<UBaseGrappleHandler> grappleHandler;

	UPROPERTY(Category = Grapple, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBaseGrappleHandler> grappleHandlerClass;

	TWeakObjectPtr<ABaseCharacter> lastHealthBarTraceTarget;

#pragma region BlueprintFunctionLibrary
	UPROPERTY(Category = Inputs, Replicated, BlueprintReadWrite)
	bool secondaryHold;

	UPROPERTY(Category = Inputs, BlueprintReadWrite)
	bool weaponSelectorHold;

	UPROPERTY(Category = WeaponSelector, BlueprintReadWrite)
	int32 selectedWeaponId;

	UPROPERTY(Category = WeaponSelector, BlueprintReadWrite)
	FVector inputDimensions;

	UPROPERTY(Category = Zoom, BlueprintReadWrite)
	bool zooming;

	UPROPERTY(Category = Zoom, BlueprintReadWrite)
	bool zoomBlocked;

	UPROPERTY(Category = Zoom, BlueprintReadWrite)
	FTimerHandle zoomUpdateHandle;

	UPROPERTY(Category = Wallrun, BlueprintReadWrite)
	bool wallrun;

	UPROPERTY(Category = Wallrun, BlueprintReadWrite)
	bool wallrunBlocked;

	UPROPERTY(Category = Wallrun, BlueprintReadWrite)
	FVector currentWallNormal;

	UPROPERTY(Category = Wallrun, BlueprintReadWrite)
	FRotator wallrunForward;

	UPROPERTY(Category = Wallrun, BlueprintReadWrite)
	FTimerHandle wallrunUpdateHandle;

	UPROPERTY(Category = Slide, BlueprintReadWrite)
	bool isSlideCooldown;

	UPROPERTY(Category = Slide, BlueprintReadWrite)
	FTimerHandle slideActivityHandle;

	UPROPERTY(Category = Slide, Replicated, BlueprintReadOnly)
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
#pragma region BlueprintFunctionLibrarySetters
	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void setSlideCooldown(float newSlideCooldown) final;
#pragma endregion

	UPROPERTY(Category = Camera, BlueprintReadOnly)
	float BaseTurnRate;

	UPROPERTY(Category = Camera, BlueprintReadOnly)
	float BaseLookUpRate;

private:
	void showBotHealthBar();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void onAbilityUsed();

protected:
	virtual bool checkPassiveAbilityCast() const override;

	virtual bool checkFirstAbilityCast() const override;

	virtual bool checkSecondAbilityCast() const override;

	virtual bool checkThirdAbilityCast() const override;

	virtual bool checkUltimateAbilityCast() const override;

	virtual float& getCurrentEnergy() final override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

private:
	void restoreAbilitiesCooldown();

	void restoreWeaponsCooldown();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION()
	void pressCrouch();

	UFUNCTION()
	void releaseCrouch();

	UFUNCTION()
	void pressZoom();

	UFUNCTION()
	void releaseZoom();

	UFUNCTION()
	void pressWeaponSelector();

	UFUNCTION()
	void releaseWeaponSelector();

	UFUNCTION()
	void pressGrapple();

	UFUNCTION()
	void releaseGrapple();

protected:
	void destroyDrone();

	void saveCurrentAbilitiesCooldown(ALostConnectionPlayerState* playerState);

	void saveCurrentWeaponsCooldown(ALostConnectionPlayerState* playerState);

	virtual void deathLogic() override;

public:
	ABaseDrone();

	UFUNCTION(Category = Weapons, Server, Reliable, BlueprintCallable)
	void changeToPrimaryWeapon();

	UFUNCTION(Category = Weapons, Server, Reliable, BlueprintCallable)
	void changeToSecondaryWeapon();

	UFUNCTION(Category = Ammo, Server, Unreliable, BlueprintCallable)
	void pickupAmmo(EAmmoType type, int32 count);

	UFUNCTION(Server, Reliable)
	void dropWeapon();

	UFUNCTION(Server, Reliable)
	void pickupWeapon(ADroppedWeapon* weaponToEquip);

	UFUNCTION()
	void changeWeapon();

	UFUNCTION()
	void alternativeWeaponMode();

	UFUNCTION()
	void action();

	UFUNCTION(Server, Unreliable)
	void restoreEnergy(float amount);

	void initDefaultUI();

	UFUNCTION(Category = Weapons, Server, Reliable, BlueprintCallable)
	void setPrimaryWeapon(TSubclassOf<UBaseWeapon> primaryWeapon);

	UFUNCTION(Category = Weapons, Server, Reliable, BlueprintCallable)
	void setSecondaryWeapon(TSubclassOf<UBaseWeapon> secondaryWeapon);

	UFUNCTION(Category = Weapons, BlueprintCallable)
	UBaseWeapon* getPrimaryWeapon() const;

	UFUNCTION(Category = Weapons, BlueprintCallable)
	UBaseWeapon* getSecondaryWeapon() const;

	UFUNCTION(Category = Weapons, BlueprintCallable)
	UBaseWeapon* getFirstInactiveWeapon() const;

	UFUNCTION(Category = Weapons, BlueprintCallable)
	UBaseWeapon* getSecondInactiveWeapon() const;

	TObjectPtr<USpringArmComponent> GetCameraOffset() const;

	TObjectPtr<UCameraComponent> GetFollowCamera() const;

	UFUNCTION(BlueprintCallable)
	FVector getStartActionLineTrace() const;

	UFUNCTION(BlueprintCallable)
	FVector getEndActionLineTrace() const;

	UFUNCTION(Category = Abilities, BlueprintCallable)
	TArray<UBaseAbility*> getDroneAbilities() const;

	bool getZooming() const;

	virtual void addPersonalModule(UBasePersonalModule* module) final override;

	virtual void addWeaponModule(UBaseWeaponModule* module) final override;

	virtual float getFlatDamageReduction_Implementation() const override;

	virtual float getPercentageDamageReduction_Implementation() const override;

	virtual void setEnergy_Implementation(float newEnergy) final override;

	virtual void setCurrentEnergy_Implementation(float newCurrentEnergy) final override;

	virtual void setEnergyRestorationPerSecond_Implementation(float newEnergyRestorationPerSecond) final override;

	virtual void setCooldownReduction_Implementation(float newCooldownReduction) final override;

	virtual void setDuration_Implementation(float newDuration) final override;

	virtual void setPower_Implementation(float newPower) final override;
	
	virtual void setEnergyEfficiency_Implementation(float newEnergyEfficiency) final override;
	
	virtual void setAOE_Implementation(float newAOE) final override;
	
	virtual void setCastPoint_Implementation(float newCastPoint) final override;

	UFUNCTION(Category = Abilities, BlueprintCallable)
	virtual void setCurrentAbility(UBaseAbility* ability) final override;

	virtual float getEnergy() const final override;

	virtual float getCurrentEnergy() const final override;

	virtual float getEnergyRestorationPerSecond() const final override;

	virtual float getCooldownReduction() const final override;

	virtual float getDuration() const final override;

	virtual float getPower() const final override;

	virtual float getEnergyEfficiency() const final override;

	virtual float getAOE() const final override;

	virtual float getCastPoint() const final override;

	virtual int32 getWeaponCount() const override;

	virtual TArray<TWeakObjectPtr<UBaseWeapon>> getWeapons() const override;

	virtual UBaseAbility* getCurrentAbility() const final override; 

	virtual UBasePassiveAbility* getPassiveAbility() const final override;

	virtual UBaseAbility* getFirstAbility() const final override;

	virtual UBaseAbility* getSecondAbility() const final override;

	virtual UBaseAbility* getThirdAbility() const final override;

	UBaseUltimateAbility* getUltimateAbility() const final override;

	virtual const TArray<UAnimMontage*>& getAbilitiesAnimations() const final override;

	UFUNCTION(Category = Modules, BlueprintCallable)
	virtual TArray<UBasePersonalModule*> getPersonalEquippedModules() const final override;

	UFUNCTION(Category = Modules, BlueprintCallable)
	virtual TArray<UBasePersonalModule*> getPersonalUnequippedModules() const final override;

	UFUNCTION(Category = Modules, BlueprintCallable)
	virtual TArray<UBaseWeaponModule*> getWeaponModules() const final override;

	virtual void castPassiveAbilityVisual() override;

	UFUNCTION(Category = Abilities, BlueprintCallable)
	virtual void castPassiveAbilityLogic() override;

	virtual void castFirstAbilityVisual() override;

	UFUNCTION(Category = Abilities, BlueprintCallable)
	virtual void castFirstAbilityLogic() override;

	virtual void castSecondAbilityVisual() override;

	UFUNCTION(Category = Abilities, BlueprintCallable)
	virtual void castSecondAbilityLogic() override;

	virtual void castThirdAbilityVisual() override;

	UFUNCTION(Category = Abilities, BlueprintCallable)
	virtual void castThirdAbilityLogic() override;

	virtual void castUltimateAbilityVisual() override;

	UFUNCTION(Category = Abilities, BlueprintCallable)
	virtual void castUltimateAbilityLogic() override;

	virtual ~ABaseDrone() = default;

	friend class ALostConnectionPlayerController;
};

inline TObjectPtr<USpringArmComponent> ABaseDrone::GetCameraOffset() const
{
	return CameraOffset;
}

inline TObjectPtr<UCameraComponent> ABaseDrone::GetFollowCamera() const
{
	return FollowCamera;
}

FORCEINLINE void ABaseDrone::showBotHealthBar()
{
	FCollisionQueryParams ignoreParameters;
	FHitResult hit;
	FVector start = FollowCamera->GetComponentLocation();
	FVector end = start + FollowCamera->GetForwardVector() * UConstants::showHealthBarDistance;

	ignoreParameters.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_Visibility, ignoreParameters);

	ABaseCharacter* character = Cast<ABaseCharacter>(hit.GetActor());

	if (lastHealthBarTraceTarget.IsValid() && hit.GetActor() != lastHealthBarTraceTarget)
	{
		if (!lastHealthBarTraceTarget->isDamaged())
		{
			lastHealthBarTraceTarget->setHealthBarVisibility(ESlateVisibility::Hidden);
		}
	}

	if (!hit.HasValidHitObjectHandle() || !character)
	{
		return;
	}

	lastHealthBarTraceTarget = character;

	lastHealthBarTraceTarget->updateHealthBar();

	lastHealthBarTraceTarget->setHealthBarVisibility(ESlateVisibility::Visible);
}

inline UBaseWeapon* ABaseDrone::getPrimaryWeapon() const
{
	return Utility::getPlayerState(this)->getPrimaryWeapon();
}

inline UBaseWeapon* ABaseDrone::getSecondaryWeapon() const
{
	return Utility::getPlayerState(this)->getSecondaryWeapon();
}

inline UBaseWeapon* ABaseDrone::getFirstInactiveWeapon() const
{
	return Utility::getPlayerState(this)->getFirstInactiveWeapon();
}

inline UBaseWeapon* ABaseDrone::getSecondInactiveWeapon() const
{
	return Utility::getPlayerState(this)->getSecondInactiveWeapon();
}
