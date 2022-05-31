// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Network/NetworkObject.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

#include "DamageInflictorUtility.generated.h"

UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class LOSTCONNECTION_API UDamageInflictorUtility :
	public UNetworkObject,
	public IDamageInflictor
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float baseInflictorDamage;

	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float addedInflictorDamage;

	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float additionalInflictorDamage;

	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	TArray<float> increasedInflictorDamageCoefficients;

	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	TArray<float> moreInflictorDamageCoefficients;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UDamageInflictorUtility() = default;

	void appendIncreaseDamageCoefficient(float coefficient) override;

	void removeIncreaseDamageCoefficient(float coefficient) override;

	void appendMoreDamageCoefficient(float coefficient) override;

	void removeMoreDamageCoefficient(float coefficient) override;

	UFUNCTION(Server, Reliable)
	void setBaseDamage(float newDamage) override;

	UFUNCTION(Server, Reliable)
	void setAddedDamage(float newAddedDamage) override;

	UFUNCTION(Server, Reliable)
	void setAdditionalDamage(float newAdditionalDamage) override;

	float getBaseDamage() const override;

	float getAddedDamage() const override;

	float getAdditionalDamage() const override;

	const TArray<float>& getIncreaseDamageCoefficients() const override;

	const TArray<float>& getMoreDamageCoefficients() const override;

	~UDamageInflictorUtility() = default;
};
