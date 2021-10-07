// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Net/DataBunch.h"

#include "Weapons/BaseWeapon.h"
#include "WorldPlaceables/DroppedWeapon.h"
#include "Utility/TimersUtility.h"
#include "Interfaces/Gameplay/Descriptions/ShotThrough.h"
#include "Interfaces/Gameplay/Actions/MovementActions.h"
#include "Interfaces/Gameplay/AnimatedActions/Reload.h"
#include "Interfaces/Gameplay/AnimatedActions/Shoot.h"
#include "Interfaces/Gameplay/AnimatedActions/Death.h"

#include "BaseCharacter.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseCharacter :
	public ACharacter,
	public IShotThrough,
	public IReload,
	public IShoot,
	public IMovementActions,
	public IDeath
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* currentWeaponMesh;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* magazine;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = onCurrentWeaponChange)
	UBaseWeapon* currentWeapon;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, Replicated)
	UBaseWeapon* defaultWeaponSlot;

protected:
	UPROPERTY()
	UTimersUtility* timers;

protected:
	UPROPERTY(Category = Stats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float health;

	UPROPERTY(Category = Stats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float currentHealth;

	UPROPERTY(Category = Stats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float defaultMovementSpeed;

	UPROPERTY(Category = Stats, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float sprintMovementSpeed;

	UPROPERTY(Category = Properties, VisibleAnywhere, Replicated, BlueprintReadOnly)
	bool isAlly;

	UPROPERTY(Category = Properties, VisibleAnywhere, Replicated, BlueprintReadOnly)
	bool isDead;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, Replicated, BlueprintReadOnly)
	TArray<int32> spareAmmo;

#pragma region BlueprintFunctionLibrary
	UPROPERTY(Category = Reloading, VisibleAnywhere, BlueprintReadWrite)
	bool isReloading;

	UPROPERTY(Category = Inputs, VisibleAnywhere, BlueprintReadWrite)
	bool jumpHold;

	UPROPERTY(Category = Inputs, VisibleAnywhere, BlueprintReadWrite)
	bool sprintHold;

	UPROPERTY(Category = Inputs, VisibleAnywhere, BlueprintReadWrite)
	bool crouchHold;

	UPROPERTY(Category = Inputs, VisibleAnywhere, BlueprintReadWrite)
	bool primaryHold;

	UPROPERTY(Category = Materials, VisibleAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* characterMaterial;

	UPROPERTY(Category = Death, VisibleAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* deathMaskRenderTexture;

	UPROPERTY(Category = Death, VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle deathUpdateHandle;

	UPROPERTY(Category = Shoot, VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle shootUpdateHandle;
#pragma endregion

#pragma region BlueprintFunctionLibraryEvents
	UFUNCTION(Category = Death, BlueprintNativeEvent, BlueprintCallable)
	void deathMaterialTimerUpdate();

	UFUNCTION(Category = Shoot, BlueprintNativeEvent, BlueprintCallable)
	void shootTimerUpdate();
#pragma endregion

private:
	UFUNCTION()
	void onCurrentWeaponChange();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

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

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void runReloadLogic() final;
#pragma endregion

#pragma region Shoot
protected:
	virtual void shootVisual() override;

	virtual void shootLogic() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void runShootLogic() final;
#pragma endregion

#pragma region Death
protected:
	virtual void deathVisual() override;

	virtual void deathLogic() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void runDeathLogic() final;
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
	virtual void changeToDefaultWeapon() final;

	UFUNCTION(BlueprintCallable)
	virtual void restoreHealth(float amount) final;

	UFUNCTION(BlueprintCallable)
	virtual void takeDamage(float amount) final;

	UFUNCTION(Server, Reliable)
	virtual void setHealth(float newHealth) final;

	UFUNCTION(Server, Reliable)
	virtual void setCurrentHealth(float newCurrentHealth) final;

	UFUNCTION(Server, Reliable)
	virtual void setDefaultMovementSpeed(float speed);

	UFUNCTION(Server, Reliable)
	virtual void setSprintMovementSpeed(float speed);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void setIsAlly(bool newIsAlly) final;

	UFUNCTION(Server, Reliable)
	virtual void setIsDead(bool newIsDead) final;

	virtual float getHealth() const final;

	virtual float getCurrentHealth() const final;

	virtual float getDefaultMovementSpeed() const final;

	virtual float getSprintMovementSpeed() const final;

	virtual bool getIsAlly() const final;

	virtual bool getIsDead() const final;

	UFUNCTION(BlueprintCallable)
	virtual int32 getSpareAmmo(ammoTypes type) const final;

	virtual bool getIsReloading() const final;

	UFUNCTION(BlueprintCallable)
	virtual bool isWeaponEquipped() const final;

	virtual USkeletalMeshComponent* getCurrentWeaponMesh() const final;

	UFUNCTION(BlueprintCallable)
	virtual int getWeaponCount() const;

	virtual float getFlatDamageReduction_Implementation() const override;

	virtual float getPercentageDamageReduction_Implementation() const override;

	virtual ~ABaseCharacter() = default;
};

inline bool ABaseCharacter::isWeaponEquipped() const
{
	return static_cast<bool>(currentWeapon);
}
