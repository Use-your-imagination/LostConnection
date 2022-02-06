// Copyright (c) 2021 Use-your-imagination

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
#include "BaseBot.h"

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
	public IMainModulesHolder,
	public IWeaponModulesHolder
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* CameraOffset;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* FollowCamera;

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
	abilitySlot abilityId;

	UPROPERTY(Category = Abilities, BlueprintReadOnly)
	UBaseAbility* currentAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UBasePassiveAbility* passiveAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UBaseAbility* firstAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UBaseAbility* secondAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UBaseAbility* thirdAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UBaseUltimateAbility* ultimateAbility;

	UPROPERTY(Category = Animations, EditDefaultsOnly, BlueprintReadOnly)
	TArray<UAnimMontage*> abilitiesAnimations;

	UPROPERTY(Category = Death, EditDefaultsOnly, BlueprintReadOnly)
	bool isFullyDestruction;

	TWeakObjectPtr<class ABaseBot> lastHealthBarTraceTarget;

#pragma region BlueprintFunctionLibrary
	UPROPERTY(Category = Inputs, BlueprintReadWrite)
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

protected:
	void destroyDrone();

	void saveCurrentAbilitiesCooldown(ALostConnectionPlayerState* playerState);

	void saveCurrentWeaponsCooldown(ALostConnectionPlayerState* playerState);

	virtual void deathLogic() override;

public:
	ABaseDrone();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void setPrimaryWeapon(TSubclassOf<UBaseWeapon> primaryWeapon);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void setSecondaryWeapon(TSubclassOf<UBaseWeapon> secondaryWeapon);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void changeToPrimaryWeapon();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void changeToSecondaryWeapon();

	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void pickupAmmo(ammoTypes type, int32 count);

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

	UFUNCTION(Category = Weapons, BlueprintCallable)
	UBaseWeapon* getPrimaryWeapon() const;

	UFUNCTION(Category = Weapons, BlueprintCallable)
	UBaseWeapon* getSecondaryWeapon() const;

	UFUNCTION(Category = Weapons, BlueprintCallable)
	UBaseWeapon* getFirstInactiveWeapon() const;

	UFUNCTION(Category = Weapons, BlueprintCallable)
	UBaseWeapon* getSecondInactiveWeapon() const;

	USpringArmComponent* GetCameraOffset() const;

	UCameraComponent* GetFollowCamera() const;

	UFUNCTION(BlueprintCallable)
	FVector getStartActionLineTrace() const;

	UFUNCTION(BlueprintCallable)
	FVector getEndActionLineTrace() const;

	UFUNCTION(Category = Abilities, BlueprintCallable)
	TArray<UBaseAbility*> getDroneAbilities() const;

	bool getZooming() const;

	virtual void addMainModule(IMainModule* module) final override;

	virtual void addWeaponModule(IWeaponModule* module) final override;

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

	UFUNCTION(BlueprintCallable)
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
	virtual const TArray<UNetworkObject*>& getMainModules() const final override;

	UFUNCTION(Category = Modules, BlueprintCallable)
	virtual const TArray<UNetworkObject*>& getWeaponModules() const final override;

	virtual void castPassiveAbilityVisual() override;

	UFUNCTION(BlueprintCallable)
	virtual void castPassiveAbilityLogic() override;

	virtual void castFirstAbilityVisual() override;

	UFUNCTION(BlueprintCallable)
	virtual void castFirstAbilityLogic() override;

	virtual void castSecondAbilityVisual() override;

	UFUNCTION(BlueprintCallable)
	virtual void castSecondAbilityLogic() override;

	virtual void castThirdAbilityVisual() override;

	UFUNCTION(BlueprintCallable)
	virtual void castThirdAbilityLogic() override;

	virtual void castUltimateAbilityVisual() override;

	UFUNCTION(BlueprintCallable)
	virtual void castUltimateAbilityLogic() override;

	virtual ~ABaseDrone() = default;

	friend class ALostConnectionPlayerController;
};

inline USpringArmComponent* ABaseDrone::GetCameraOffset() const
{
	return CameraOffset;
}

inline UCameraComponent* ABaseDrone::GetFollowCamera() const
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

	ABaseBot* bot = Cast<ABaseBot>(hit.Actor);

	if (lastHealthBarTraceTarget.IsValid() && hit.Actor != lastHealthBarTraceTarget)
	{
		if (!lastHealthBarTraceTarget->isDamaged())
		{
			lastHealthBarTraceTarget->setHealthBarVisibility(false);
		}
	}

	if (!hit.Actor.IsValid() || !bot)
	{
		return;
	}

	lastHealthBarTraceTarget = bot;

	lastHealthBarTraceTarget->updateHealthBar();

	lastHealthBarTraceTarget->setHealthBarVisibility(true);
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
