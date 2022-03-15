// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerInput.h"
#include "Net/UnrealNetwork.h"
#include "NiagaraSystem.h"

#include "Interfaces/Gameplay/Statuses/Base/AilmentInflictor.h"

#include "SN4K3PassiveAbilityHead.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API ASN4K3PassiveAbilityHead :
	public ACharacter,
	public IAilmentInflictor
{
	GENERATED_BODY()

private:
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

	bool isExploded;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION(BlueprintCallable)
	void explode();

	void destroyHead();

public:
	ASN4K3PassiveAbilityHead();

	UFUNCTION(Category = RBM, BlueprintNativeEvent, BlueprintCallable)
	void speedup();

	UFUNCTION(Category = Checks, BlueprintNativeEvent, BlueprintCallable)
	bool checkExplode();

	UFUNCTION(Category = Checks, BlueprintNativeEvent, BlueprintCallable)
	bool checkSpeedup();

	virtual void Tick(float DeltaTime) override;

	ETypeOfDamage getDamageType() const override;

	float getBaseCrushingHitChance() const override;

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
