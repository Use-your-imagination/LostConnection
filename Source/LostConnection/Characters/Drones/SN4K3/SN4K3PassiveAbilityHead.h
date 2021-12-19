// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Net/UnrealNetwork.h"
#include "NiagaraSystem.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Interfaces/Gameplay/Statuses/Base/AilmentInflictor.h"

#include "SN4K3PassiveAbilityHead.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API ASN4K3PassiveAbilityHead :
	public APawn,
	public IAilmentInflictor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	USphereComponent* sphere;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* mesh;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* movement;

	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* explosionParticles;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float naniteExplosionDamage;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float explosionRadius;

	UPROPERTY(Category = DamageInflictor, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float addedDamage;

	UPROPERTY(Category = DamageInflictor, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float additionalDamage;

	UPROPERTY(Category = DamageInflictor, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<float> increasedDamageCoefficients;

	UPROPERTY(Category = DamageInflictor, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<float> moreDamageCoefficients;

	UPROPERTY(Category = Cooldown, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float cooldown;

	UPROPERTY(Category = Cooldown, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float currentCooldown;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION()
	void explode();

	void explodeVFX();

public:	
	ASN4K3PassiveAbilityHead();

	UFUNCTION(Category = RBM, BlueprintNativeEvent, BlueprintCallable)
	void speedup();

	virtual UPawnMovementComponent* GetMovementComponent() const final override;

	virtual void Tick(float DeltaTime) override;

	typeOfDamage getDamageType() const override;

	float getCrushingHitChance() const override;

	float getAdditionalCrushingHitChance() const override;

	void appendIncreasedDamageCoefficient(float coefficient) override;

	void removeIncreasedDamageCoefficient(float coefficient) override;

	void appendMoreDamageCoefficient(float coefficient) override;

	void removeMoreDamageCoefficient(float coefficient) override;

	void setBaseDamage(float damage) override;

	void setAddedDamage(float addedDamage) override;

	void setAdditionalDamage(float additionalDamage) override;

	float getBaseDamage() const override;

	float getAddedDamage() const override;

	float getAdditionalDamage() const override;

	TArray<float> getIncreasedDamageCoefficients() const override;

	TArray<float> getMoreDamageCoefficients() const override;

	virtual ~ASN4K3PassiveAbilityHead() = default;
};
