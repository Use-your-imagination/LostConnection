// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Net/UnrealNetwork.h"

#include "Interfaces/Gameplay/Descriptions/ShotThrough.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentInflictor.h"

#include "SN4K3PassiveAbilityHead.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API ASN4K3PassiveAbilityHead :
	public APawn,
	public IShotThrough,
	public IAilmentInflictor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* capsule;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* mesh;

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

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	ASN4K3PassiveAbilityHead();

	virtual void Tick(float DeltaTime) override;

	void impactAction_Implementation(class ABaseAmmo* ammo, const FHitResult& hit) final override;

	float getFlatDamageReduction_Implementation() const override;

	float getPercentageDamageReduction_Implementation() const override;

	typeOfDamage getDamageType() const override;

	float getCrushingHitChance() const override;

	float getAdditionalCrushingHitChance() const override;

	void appendIncreasedDamageCoefficient(float coefficient);

	void removeIncreasedDamageCoefficient(float coefficient);

	void appendMoreDamageCoefficient(float coefficient);

	void removeMoreDamageCoefficient(float coefficient);

	void setBaseDamage(float damage);

	void setAddedDamage(float addedDamage);

	void setAdditionalDamage(float additionalDamage);

	float getBaseDamage() const;

	float getAddedDamage() const;

	float getAdditionalDamage() const;

	TArray<float> getIncreasedDamageCoefficients() const;

	TArray<float> getMoreDamageCoefficients() const;

	virtual ~ASN4K3PassiveAbilityHead() = default;
};
