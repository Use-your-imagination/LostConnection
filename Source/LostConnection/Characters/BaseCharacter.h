// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Net/DataBunch.h"

#include "Engine/LostConnectionPlayerState.h"
#include "WorldPlaceables/DroppedWeapon.h"
#include "Utility/TimersUtility.h"
#include "Utility/Utility.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "Interfaces/Gameplay/Descriptions/ShotThrough.h"
#include "Interfaces/Gameplay/Actions/MovementActions.h"
#include "Interfaces/Gameplay/AnimatedActions/Reload.h"
#include "Interfaces/Gameplay/AnimatedActions/Shoot.h"
#include "Interfaces/Gameplay/AnimatedActions/Death.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Interfaces/Gameplay/Descriptions/ObserverHolders/GameplayEvents/DeathEventsHolder.h"
#include "Interfaces/Gameplay/Descriptions/AITargeted.h"

#include "BaseCharacter.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API ABaseCharacter :
	public ACharacter,
	public IShotThrough,
	public IReload,
	public IShoot,
	public IMovementActions,
	public IDeath,
	public IAilmentReceiver,
	public IDeathEventsHolder,
	public IAITargeted
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* currentWeaponMesh;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* magazine;

	UPROPERTY(Category = VFX, VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* underStatusComponent;

	UPROPERTY(Category = Weapons, ReplicatedUsing = onCurrentWeaponChange, BlueprintReadOnly)
	UBaseWeapon* currentWeapon;

protected:
	TimersUtility timers;

protected:
	UPROPERTY(Category = CharacterInformation, EditDefaultsOnly, BlueprintReadOnly)
	FText characterName;

	UPROPERTY(Category = CharacterInformation, EditDefaultsOnly, BlueprintReadOnly)
	FText description;

	UPROPERTY(Category = Stats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float health;

	UPROPERTY(Category = Stats, EditDefaultsOnly, ReplicatedUsing = onCurrentHealthChanged, BlueprintReadOnly)
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

	UPROPERTY(Category = Materials, BlueprintReadWrite)
	UMaterialInstanceDynamic* characterMaterial;

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
	virtual void onCurrentHealthChanged();

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

#pragma region Reload
protected:
	virtual void reloadVisual() override;

	virtual void reloadLogic() override;
#pragma endregion

#pragma region Death
protected:
	virtual void deathVisual() override;

	virtual void deathLogic() override;
#pragma endregion

public:	
	ABaseCharacter();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void runDeathLogic();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void runReloadLogic();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void changeToDefaultWeapon();

	UFUNCTION(BlueprintCallable)
	void restoreHealth(float amount);

	void returnAmmoToSpare(UBaseWeapon* weapon);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void setDefaultWeapon(TSubclassOf<UBaseWeapon> defaultWeapon);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void setHealth(float newHealth);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void setCurrentHealth(float newCurrentHealth);

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

	float getCurrentHealth() const;

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

	TimersUtility& getTimers();

	UFUNCTION(Server, Reliable, BlueprintCallable)
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

	UFUNCTION(NetMulticast, Reliable)
	virtual void setUnderStatusIntVariable(const FString& key, int32 value) final override;

	virtual const TArray<UBaseStatus*>& getStatuses() const final override;

	virtual bool getIsAlly() const final override;

	virtual bool getIsDead() const final override;

	virtual float getFlatDamageReduction_Implementation() const override;

	virtual float getPercentageDamageReduction_Implementation() const override;

	virtual float getTotalLifePercentDealt(class IDamageInflictor* inflictor) const final override;

	virtual float getHealthPercentDealt(class IDamageInflictor* inflictor) const final override;

	virtual void statusInflictorImpactAction(const TScriptInterface<class IStatusInflictor>& inflictor, const FHitResult& hit) final override;

	virtual USkeletalMeshComponent* getMeshComponent() final override;

	virtual UCapsuleComponent* getCapsuleComponent() final override;

	virtual const TArray<IOnDeathEvent*>& getDeathEvents() const final override;

	virtual ~ABaseCharacter() = default;
};

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
	return IsValid(currentWeapon);
}
