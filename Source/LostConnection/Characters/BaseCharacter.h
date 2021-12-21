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

USTRUCT()
struct FAmmoData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	ammoTypes ammoType;

	UPROPERTY()
	int32 ammoCount;

	FAmmoData(ammoTypes ammoType = ammoTypes::large, int32 ammoCount = 0);
};

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

	UPROPERTY(Category = AmmoSettings, EditDefaultsOnly, BlueprintReadOnly)
	TMap<ammoTypes, int32> spareAmmo;

	UPROPERTY(ReplicatedUsing = onSpareAmmoChanged)
	TArray<FAmmoData> spareAmmoReplication;

	UPROPERTY(Category = PhysicalConstraints, EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> physicsBones;

	UPROPERTY(Category = Statuses, Replicated, BlueprintReadOnly)
	TArray<UBaseStatus*> statuses;

	TWeakObjectPtr<class USwarmAilment> swarm;

	TArray<TWeakInterfacePtr<IOnDeathEvent>> deathEvents;

#pragma region BlueprintFunctionLibrary
	UPROPERTY(Category = Reloading, BlueprintReadWrite)
	bool isReloading;

	UPROPERTY(Category = Inputs, BlueprintReadWrite)
	bool jumpHold;

	UPROPERTY(Category = Inputs, BlueprintReadWrite)
	bool sprintHold;

	UPROPERTY(Category = Inputs, BlueprintReadWrite)
	bool crouchHold;

	UPROPERTY(Category = Inputs, BlueprintReadWrite)
	bool primaryHold;

	UPROPERTY(Category = Materials, BlueprintReadWrite)
	UMaterialInstanceDynamic* characterMaterial;

	UPROPERTY(Category = Death, BlueprintReadWrite)
	UTextureRenderTarget2D* deathMaskRenderTexture;

	UPROPERTY(Category = Death, BlueprintReadWrite)
	FTimerHandle deathUpdateHandle;

	UPROPERTY(Category = Shoot, BlueprintReadWrite)
	FTimerHandle shootUpdateHandle;
#pragma endregion

#pragma region BlueprintFunctionLibraryEvents
	UFUNCTION(Category = Death, BlueprintNativeEvent, BlueprintCallable)
	void deathMaterialTimerUpdate();

	UFUNCTION(Category = Shoot, BlueprintNativeEvent, BlueprintCallable)
	void shootTimerUpdate();
#pragma endregion

protected:
	UFUNCTION()
	void onCurrentWeaponChange();

	UFUNCTION()
	void onSpareAmmoChanged();

	UFUNCTION()
	virtual void onCurrentHealthChanged();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	virtual void PostInitializeComponents() override;

protected:
	virtual void updateWeaponMesh() final;

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

#pragma region Shoot
protected:
	virtual void shootVisual() override;

	virtual void shootLogic() override;
#pragma endregion

#pragma region Death
protected:
	virtual void deathVisual() override;

	virtual void deathLogic() override;
#pragma endregion

	UFUNCTION()
	void resetShootLogic();

public:	
	ABaseCharacter();

	UFUNCTION(BlueprintCallable)
	virtual void shoot();

	UFUNCTION(BlueprintCallable)
	virtual void resetShoot();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void runShootLogic() final;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void runDeathLogic() final;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void runReloadLogic() final;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void changeToDefaultWeapon() final;

	UFUNCTION(BlueprintCallable)
	virtual void restoreHealth(float amount) final;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void setDefaultWeapon(TSubclassOf<UBaseWeapon> defaultWeapon) final;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void setHealth(float newHealth) final;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void setCurrentHealth(float newCurrentHealth) final;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void setReservedHealth(float newReservedHealth) final;

	UFUNCTION(Server, Reliable)
	virtual void setDefaultMovementSpeed(float speed) final;

	UFUNCTION(Server, Reliable)
	virtual void setSprintMovementSpeed(float speed) final;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void setIsAlly(bool newIsAlly) final;

	UFUNCTION(Server, Reliable)
	virtual void setIsDead(bool newIsDead) final;

	UFUNCTION(Category = Weapons, BlueprintCallable)
	virtual UBaseWeapon* getDefaultWeapon() final;

	virtual float getHealth() const final;

	virtual float getCurrentHealth() const final;

	virtual float getReservedHealth() const final;

	virtual float getDefaultMovementSpeed() const final;

	virtual float getSprintMovementSpeed() const final;

	UFUNCTION(BlueprintCallable)
	virtual int32 getSpareAmmo(ammoTypes type) const final;

	virtual bool getIsReloading() const final;

	UFUNCTION(BlueprintCallable)
	virtual bool isWeaponEquipped() const final;

	virtual USkeletalMeshComponent* getCurrentWeaponMeshComponent() const final;

	virtual UBaseWeapon* getCurrentWeapon() final;

	UFUNCTION(BlueprintCallable)
	virtual int32 getWeaponCount() const;

	virtual const TWeakObjectPtr<class USwarmAilment>& getSwarm() const final;

	virtual TArray<TWeakObjectPtr<UBaseWeapon>> getWeapons() const;

	UFUNCTION(BlueprintCallable)
	virtual void takeDamage(const TScriptInterface<class IDamageInflictor>& inflictor) final override;

	virtual void impactAction_Implementation(ABaseAmmo* ammo, const FHitResult& hit) override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void spawnStatusVFX(UNiagaraSystem* statusVFX, const FHitResult& hit) final override;

	virtual void addStatus(class UBaseStatus* status) final override;

	virtual void applySwarmAilment(class USwarmAilment* swarm) final override;

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

	virtual void attachDeathEvent(IOnDeathEvent* event) final override;

	virtual void detachDeathEvent(IOnDeathEvent* event) final override;

	virtual const TArray<TWeakInterfacePtr<IOnDeathEvent>>& getDeathEvents() const final override;

	virtual ~ABaseCharacter() = default;
};

inline bool ABaseCharacter::isWeaponEquipped() const
{
	return StaticCast<bool>(currentWeapon);
}
