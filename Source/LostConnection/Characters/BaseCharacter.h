// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Net/DataBunch.h"
#include "Components/TimelineComponent.h"

#include "Engine/LostConnectionPlayerState.h"
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
#include "Interfaces/Gameplay/Descriptions/ObserverHolders/GameplayEvents/DeathEventsHolder.h"
#include "Interfaces/Gameplay/Descriptions/AITargeted.h"
#include "Interfaces/Gameplay/Timelines/DeathTimeline.h"

#include "BaseCharacter.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API ABaseCharacter :
	public ACharacter,
	public IShotThrough,
	public IReload,
	public IShoot,
	public IMovementActions,
	public IDeath,
	public IAilmentReceiver,
	public IDeathEventsHolder,
	public IAITargeted,
	public IDeathTimeline
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* currentWeaponMesh;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* magazine;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* underStatusComponent;

	UPROPERTY(Category = Weapons, ReplicatedUsing = onCurrentWeaponChange, BlueprintReadOnly)
	UBaseWeapon* currentWeapon;

	UPROPERTY(Category = Timelines, BlueprintReadWrite)
	UTimelinesUtility* timelines;

	UPROPERTY(Category = EnergyShield, ReplicatedUsing = onEnergyShieldUpdate, BlueprintReadOnly)
	UBaseEnergyShield* energyShield;

	UPROPERTY(Category = EnergyShield, EditDefaultsOnly, BlueprintReadOnly)
	float startEnergyShieldCapacity;

private:
	UPROPERTY(Category = Classes, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
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

	UPROPERTY(Category = Defaults, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int32 maxSmallAmmoCount;

	UPROPERTY(Category = Defaults, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int32 maxLargeAmmoCount;

	UPROPERTY(Category = Defaults, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int32 maxEnergyAmmoCount;

	UPROPERTY(Category = Defaults, EditDefaultsOnly, BlueprintReadOnly)
	int32 defaultSmallAmmoCount;

	UPROPERTY(Category = Defaults, EditDefaultsOnly, BlueprintReadOnly)
	int32 defaultLargeAmmoCount;

	UPROPERTY(Category = Defaults, EditDefaultsOnly, BlueprintReadOnly)
	int32 defaultEnergyAmmoCount;

	UPROPERTY(Category = PhysicalConstraints, EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> physicsBones;

	UPROPERTY(Category = Statuses, Replicated, BlueprintReadOnly)
	TArray<UBaseStatus*> statuses;

	TWeakObjectPtr<class USwarmAilment> swarm;

	TArray<IOnDeathEvent*> deathEvents;

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

public:	
	ABaseCharacter();

	UFUNCTION(BlueprintCallable)
	void runReloadLogic();

	UFUNCTION(BlueprintCallable)
	void runDeathLogic();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void changeToDefaultWeapon();

	UFUNCTION(BlueprintCallable)
	void restoreHealth(float amount);

	void returnAmmoToSpare(UBaseWeapon* weapon);

	bool isDamaged() const;

	UFUNCTION(NetMulticast, Unreliable)
	void playAnimation(UAnimMontage* animation);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void setDefaultWeapon(TSubclassOf<UBaseWeapon> defaultWeapon);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void setHealth(float newHealth);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void setReservedHealth(float newReservedHealth);

	UFUNCTION(Server, Reliable)
	void setDefaultMovementSpeed(float speed);

	UFUNCTION(Server, Reliable)
	void setSprintMovementSpeed(float speed);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void setIsAlly(bool newIsAlly);

	UFUNCTION(Server, Reliable)
	void setIsDead(bool newIsDead);

	UFUNCTION(Category = Weapons, BlueprintCallable)
	UBaseWeapon* getDefaultWeapon();

	float getHealth() const;

	float getReservedHealth() const;

	float getDefaultMovementSpeed() const;

	float getSprintMovementSpeed() const;

	UFUNCTION(BlueprintCallable)
	int32 getSpareAmmo(ammoTypes type) const;

	bool getIsReloading() const;

	UFUNCTION(BlueprintCallable)
	bool isWeaponEquipped() const;

	USkeletalMeshComponent* getCurrentWeaponMeshComponent() const;

	UBaseWeapon* getCurrentWeapon() const;

	UFUNCTION(BlueprintCallable)
	virtual int32 getWeaponCount() const;

	const TWeakObjectPtr<class USwarmAilment>& getSwarm() const;

	virtual TArray<TWeakObjectPtr<UBaseWeapon>> getWeapons() const;

	int32 getDefaultSmallAmmoCount() const;

	int32 getDefaultLargeAmmoCount() const;

	int32 getDefaultEnergyAmmoCount() const;

	float getStartEnergyShieldCapacity() const;

	TimersUtility& getTimers();

	UFUNCTION(Server, Unreliable, BlueprintCallable)
	virtual void shoot() final override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void resetShoot() final override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void takeDamage(const TScriptInterface<class IDamageInflictor>& inflictor) final override;

	virtual void impactAction_Implementation(AAmmo* ammo, const FHitResult& hit) override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void spawnStatusVFX(UNiagaraSystem* statusVFX, const FHitResult& hit) final override;

	virtual void addStatus(class UBaseStatus* status) final override;

	virtual void applySwarmAilment(class USwarmAilment* swarm) final override;

	virtual void attachDeathEvent(IOnDeathEvent* event) final override;

	virtual void detachDeathEvent(IOnDeathEvent* event) final override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void setCurrentHealth(float newCurrentHealth) final override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void setUnderStatusIntVariable(const FString& key, int32 value) final override;

	virtual float getCurrentHealth() const final override;

	virtual const TArray<UBaseStatus*>& getStatuses() const final override;

	virtual bool getIsAlly() const final override;

	virtual bool getIsDead() const final override;

	virtual float getFlatDamageReduction_Implementation() const override;

	virtual float getPercentageDamageReduction_Implementation() const override;

	virtual float getTotalLifePool() const override;

	virtual float getLifePool() const override;

	virtual float getEnergyShieldPool() const override;

	virtual float getTotalLifePercentDealt(class IDamageInflictor* inflictor) const final override;

	virtual float getLifePercentDealt(class IDamageInflictor* inflictor) const final override;

	virtual float getEnergyShieldPercentDealt(class IDamageInflictor* inflictor) const final override;

	virtual void statusInflictorImpactAction(const TScriptInterface<class IStatusInflictor>& inflictor, const FHitResult& hit) final override;

	virtual USkeletalMeshComponent* getMeshComponent() final override;

	virtual UCapsuleComponent* getCapsuleComponent() final override;

	virtual const TArray<IOnDeathEvent*>& getDeathEvents() const final override;

	UFUNCTION(Category = Timelines, BlueprintNativeEvent, BlueprintCallable)
	void deathTimelineUpdate(float value) override;

	UFUNCTION(Category = Timelines, BlueprintNativeEvent, BlueprintCallable)
	void deathTimelineFinished() override;

	virtual ~ABaseCharacter() = default;
};

inline bool ABaseCharacter::isDamaged() const
{
	return (currentHealth < health) ||
		(IsValid(energyShield) && energyShield->getCurrentCapacity() < energyShield->getCapacity());
}

inline int32 ABaseCharacter::getSpareAmmo(ammoTypes type) const
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
