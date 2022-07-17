// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Net/DataBunch.h"
#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"

#include "WorldPlaceables/DroppedWeapon.h"
#include "Utility/TimersUtility.h"
#include "Utility/TimelinesUtility.h"
#include "Utility/Utility.h"
#include "EnergyShields/BaseEnergyShield.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "Interfaces/Gameplay/Descriptions/ShotThrough.h"
#include "Interfaces/Gameplay/Actions/MovementActions.h"
#include "Interfaces/Gameplay/AnimatedActions/Reload.h"
#include "Interfaces/Gameplay/AnimatedActions/Shoot.h"
#include "Interfaces/Gameplay/AnimatedActions/Death.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Interfaces/Gameplay/Descriptions/ObserverHolders/DeathEventsHolder.h"
#include "Interfaces/Gameplay/Descriptions/ObserverHolders/HitEventsHolder.h"
#include "Interfaces/Gameplay/Descriptions/ObserverHolders/ShotEventsHolder.h"
#include "Interfaces/Gameplay/Descriptions/ObserverHolders/TakeDamageEventsHolder.h"
#include "Interfaces/Gameplay/Descriptions/AITargeted.h"
#include "Interfaces/Gameplay/Timelines/DeathTimeline.h"
#include "UI/HealthBarWidget.h"

#include "BaseCharacter.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable)
class LOSTCONNECTION_API ABaseCharacter :
	public ACharacter,
	public IShotThrough,
	public IReload,
	public IShoot,
	public IMovementActions,
	public IDeath,
	public IAilmentReceiver,
	public IDeathEventsHolder,
	public IHitEventsHolder,
	public IShotEventsHolder,
	public ITakeDamageEventsHolder,
	public IAITargeted,
	public IDeathTimeline,
	public IPersonalModulesHolder,
	public IWeaponModulesHolder
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> currentWeaponMesh;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> magazine;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> underStatusComponent;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> healthBarWidget;

	UPROPERTY(Category = Weapons, ReplicatedUsing = onCurrentWeaponChange, BlueprintReadOnly)
	TObjectPtr<UBaseWeapon> currentWeapon;

	UPROPERTY(Category = Timelines, BlueprintReadWrite)
	TObjectPtr<UTimelinesUtility> timelines;

	UPROPERTY(Category = EnergyShield, ReplicatedUsing = onEnergyShieldUpdate, BlueprintReadOnly)
	TObjectPtr<UBaseEnergyShield> energyShield;

	UPROPERTY(Category = EnergyShield, EditDefaultsOnly, BlueprintReadOnly)
	float startEnergyShieldCapacity;

private:
	UPROPERTY(Category = Classes, EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<UBaseEnergyShield> energyShieldClass;

protected:
	TimersUtility timers;

protected:
	UPROPERTY(Category = CharacterInformation, EditDefaultsOnly, BlueprintReadOnly)
	FText characterName;

	UPROPERTY(Category = CharacterInformation, EditDefaultsOnly, BlueprintReadOnly)
	FText description;

	UPROPERTY(Category = Stats, EditDefaultsOnly, ReplicatedUsing = onHealthChange, BlueprintReadOnly)
	float health;

	UPROPERTY(Category = Stats, EditDefaultsOnly, ReplicatedUsing = onCurrentHealthChange, BlueprintReadOnly)
	float currentHealth;

	UPROPERTY(Category = Stats, Replicated, BlueprintReadOnly)
	float reservedHealth;

	UPROPERTY(Category = Stats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float defaultMovementSpeed;

	UPROPERTY(Category = Stats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float sprintMovementSpeed;

	UPROPERTY(Category = Properties, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	bool isAlly;

	UPROPERTY(Category = Properties, Replicated, BlueprintReadOnly)
	bool isDead;

	UPROPERTY(Category = Defaults, EditDefaultsOnly, BlueprintReadOnly)
	int32 defaultSmallAmmoCount;

	UPROPERTY(Category = Defaults, EditDefaultsOnly, BlueprintReadOnly)
	int32 defaultLargeAmmoCount;

	UPROPERTY(Category = Defaults, EditDefaultsOnly, BlueprintReadOnly)
	int32 defaultEnergyAmmoCount;

	UPROPERTY(Category = PhysicalConstraints, EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> physicsBones;

	UPROPERTY(Category = Statuses, Replicated, BlueprintReadOnly)
	TArray<TObjectPtr<UBaseStatus>> statuses;

	UPROPERTY(Replicated)
	TWeakObjectPtr<class USwarmAilment> swarm;

	UPROPERTY()
	TArray<TScriptInterface<IOnDeathEvent>> deathEvents;

	UPROPERTY()
	TArray<TScriptInterface<IOnHitEvent>> hitEvents;

	UPROPERTY()
	TArray<TScriptInterface<IOnShotEvent>> shotEvents;

	UPROPERTY()
	TArray<TScriptInterface<IOnTakeDamageEvent>> takeDamageEvents;

#pragma region BlueprintFunctionLibrary
	UPROPERTY(Category = Reloading, BlueprintReadWrite)
	bool isReloading;

	UPROPERTY(Category = Inputs, BlueprintReadWrite)
	bool jumpHold;

	UPROPERTY(Category = Inputs, BlueprintReadWrite)
	bool sprintHold;

	UPROPERTY(Category = Inputs, BlueprintReadWrite)
	bool crouchHold;

	UPROPERTY(Category = Death, BlueprintReadWrite)
	UTextureRenderTarget2D* deathMaskRenderTexture;

	UPROPERTY(Category = Death, BlueprintReadWrite)
	FTimerHandle deathUpdateHandle;
#pragma endregion

#pragma region BlueprintFunctionLibraryEvents
	UFUNCTION(Category = Death, BlueprintNativeEvent, BlueprintCallable)
	void deathMaterialTimerUpdate();
#pragma endregion

protected:
	UFUNCTION()
	void onCurrentWeaponChange();

	UFUNCTION()
	void onEnergyShieldUpdate();

public:
	UFUNCTION()
	virtual void onHealthChange();

	UFUNCTION()
	virtual void onCurrentHealthChange();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

protected:
	void updateWeaponMesh();

	UFUNCTION()
	virtual void holdSprint();

	UFUNCTION()
	virtual void releaseSprint();

	virtual void Jump() final override;

	virtual void StopJumping() final override;

	void setMaxSpeed(float speed);

protected:
	virtual void reloadVisual() override;

	virtual void reloadLogic() override;

	virtual void deathVisual() override;

	virtual void deathLogic() override;

protected:
	UFUNCTION()
	virtual void updateCharacterVisual();

private:
	TObjectPtr<UHealthBarWidget> getHealthBarWidget() const;

protected:
	virtual TArray<TScriptInterface<IOnDeathEvent>>& getDeathEvents() final override;

	virtual TArray<TScriptInterface<IOnHitEvent>>& getHitEvents() final override;

	virtual TArray<TScriptInterface<IOnShotEvent>>& getShotEvents() final override;

	virtual TArray<TScriptInterface<IOnTakeDamageEvent>>& getTakeDamageEvents() final override;

public:	
	ABaseCharacter();

	UFUNCTION(Category = Reload, BlueprintCallable)
	void runReloadLogic();

	UFUNCTION(Category = Death, BlueprintCallable)
	void runDeathLogic();

	UFUNCTION(Category = Weapons, Server, Reliable, BlueprintCallable)
	void changeToDefaultWeapon();

	UFUNCTION(Category = Health, BlueprintCallable)
	void restoreHealth(float amount);

	bool isDamaged() const;

	UFUNCTION(NetMulticast, Unreliable)
	void playAnimation(UAnimMontage* animation);

	UFUNCTION(Category = Visual, BlueprintCallable)
	void updateCharacterVisualCall();

	void updateHealthBar();

	UFUNCTION(Category = Health, Server, Reliable, BlueprintCallable)
	void setHealth(float newHealth);

	UFUNCTION(Category = Health, Server, Reliable, BlueprintCallable)
	void setReservedHealth(float newReservedHealth);

	UFUNCTION(Server, Reliable)
	void setDefaultMovementSpeed(float speed);

	UFUNCTION(Server, Reliable)
	void setSprintMovementSpeed(float speed);

	UFUNCTION(Category = Ally, Server, Reliable, BlueprintCallable)
	void setIsAlly(bool newIsAlly);

	UFUNCTION(Server, Reliable)
	void setIsDead(bool newIsDead);

	void setHealthBarVisibility(ESlateVisibility visibility);

	UFUNCTION(Category = Weapons, BlueprintCallable)
	UBaseWeapon* getDefaultWeapon();

	float getHealth() const;

	float getReservedHealth() const;

	float getDefaultMovementSpeed() const;

	float getSprintMovementSpeed() const;

	UFUNCTION(Category = Ammo, BlueprintCallable)
	int32 getSpareAmmo(EAmmoType type) const;

	bool getIsReloading() const;

	UFUNCTION(Category = Weapons, BlueprintCallable)
	bool isWeaponEquipped() const;

	TObjectPtr<USkeletalMeshComponent> getCurrentWeaponMeshComponent() const;

	TObjectPtr<UBaseWeapon> getCurrentWeapon() const;

	UFUNCTION(Category = Weapons, BlueprintCallable)
	virtual int32 getWeaponCount() const;

	const TWeakObjectPtr<class USwarmAilment>& getSwarm() const;

	virtual TArray<TWeakObjectPtr<UBaseWeapon>> getWeapons() const;

	int32 getDefaultSmallAmmoCount() const;

	int32 getDefaultLargeAmmoCount() const;

	int32 getDefaultEnergyAmmoCount() const;

	float getStartEnergyShieldCapacity() const;

	TimersUtility& getTimers();

	UFUNCTION(Category = Weapons, Server, Unreliable, BlueprintCallable)
	virtual void shoot() final override;

	UFUNCTION(Category = Weapons, Server, Reliable, BlueprintCallable)
	virtual void resetShoot() final override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(Server, Reliable)
	virtual void takeDamageFromInflictor(const TScriptInterface<class IDamageInflictor>& inflictor) final override;

	virtual void impactAction_Implementation(AAmmo* ammo, const FHitResult& hit) override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void spawnStatusVFX(UNiagaraSystem* statusVFX, const FHitResult& hit) final override;

	virtual void addStatus(TObjectPtr<class UBaseStatus> status) final override;

	virtual void applySwarmAilment(class USwarmAilment* swarm) final override;

	virtual void statusInflictorImpactAction(const TScriptInterface<class IStatusInflictor>& inflictor, const FHitResult& hit) final override;

	UFUNCTION(Category = Health, Server, Reliable, BlueprintCallable)
	virtual void setCurrentHealth(float newCurrentHealth) final override;

	UFUNCTION(Category = Statuses, NetMulticast, Reliable)
	virtual void setUnderStatusIntVariable(const FString& key, int32 value) final override;

	virtual float getCurrentHealth() const final override;

	virtual const TArray<TObjectPtr<UBaseStatus>>& getStatuses() const final override;

	virtual bool getIsAlly() const final override;

	virtual float getFlatDamageReduction_Implementation() const override;

	virtual float getPercentageDamageReduction_Implementation() const override;

	virtual float getTotalLifePool() const override;

	virtual float getLifePool() const override;

	virtual float getEnergyShieldPool() const override;

	virtual float getTotalLifePercentDealt(const TScriptInterface<class IDamageInflictor>& inflictor) const final override;

	virtual float getLifePercentDealt(const TScriptInterface<class IDamageInflictor>& inflictor) const final override;

	virtual float getEnergyShieldPercentDealt(const TScriptInterface<class IDamageInflictor>& inflictor) const final override;

	virtual USkeletalMeshComponent* getMeshComponent() final override;

	virtual UCapsuleComponent* getCapsuleComponent() final override;

	UFUNCTION(Category = Timelines, BlueprintNativeEvent, BlueprintCallable)
	void deathTimelineUpdate(float value) override;

	UFUNCTION(Category = Timelines, BlueprintNativeEvent, BlueprintCallable)
	void deathTimelineFinished() override;

	virtual const TArray<UInventoryCell*>& getPersonalEquippedModules() const final override;

	virtual const TArray<UInventoryCell*>& getPersonalUnequippedModules() const final override;

	virtual const TArray<TObjectPtr<UInventoryCell>>& getActivePersonalModules() const final override;

	virtual const TArray<UInventoryCell*>& getWeaponModules() const final override;

	virtual const TArray<TObjectPtr<UInventoryCell>>& getActiveWeaponModules() const final override;

	virtual ~ABaseCharacter() = default;
};

inline bool ABaseCharacter::isDamaged() const
{
	return (currentHealth < health) ||
		(IsValid(energyShield) && energyShield->getCurrentCapacity() < energyShield->getCapacity());
}

FORCEINLINE void ABaseCharacter::updateHealthBar()
{
	UHealthBarWidget* widget = this->getHealthBarWidget();
	UMaterialInstanceDynamic* healthBarMaterial = widget->getImage()->GetDynamicMaterial();
	UTextBlock* healthBarText = widget->getText();

	healthBarMaterial->SetScalarParameterValue("LifePercent", Utility::toPercent(currentHealth / health));

	if (IsValid(energyShield))
	{
		healthBarMaterial->SetScalarParameterValue("ShieldPercent", Utility::toPercent(energyShield->getCurrentCapacity() / energyShield->getCapacity()));

		healthBarText->SetText
		(
			FText::Format
			(
				FText::FromString("{0} | {1}"),
				Utility::getTextFromFloat(energyShield->getCurrentCapacity()),
				Utility::getTextFromFloat(currentHealth)
			)
		);
	}
	else
	{
		healthBarText->SetText(Utility::getTextFromFloat(currentHealth));
	}
}

inline void ABaseCharacter::setHealthBarVisibility(ESlateVisibility visibility)
{
	UHealthBarWidget* widget = this->getHealthBarWidget();

	if (!widget)
	{
		return;
	}

	widget->SetVisibility(visibility);
}

inline int32 ABaseCharacter::getSpareAmmo(EAmmoType type) const
{
	if (!GetController())
	{
		return 0;
	}

	return Utility::getPlayerState(this)->getSpareAmmo(type);
}

inline bool ABaseCharacter::getIsReloading() const
{
	return isReloading;
}

inline bool ABaseCharacter::isWeaponEquipped() const
{
	return StaticCast<bool>(currentWeapon);
}
