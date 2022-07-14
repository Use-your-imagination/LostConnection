// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Network/NetworkObject.h"

#include "DamageInflictor.generated.h"

USTRUCT(BlueprintType)
struct LOSTCONNECTION_API FDamageStructure
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, BlueprintReadOnly)
	float baseDamage;

	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, BlueprintReadOnly)
	float addedDamage;

	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, BlueprintReadOnly)
	float additionalDamage;

	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, BlueprintReadOnly)
	TArray<float> increaseDamageCoefficients;

	UPROPERTY(Category = DamageInflictor, EditDefaultsOnly, BlueprintReadOnly)
	TArray<float> moreDamageCoefficients;

public:
	FDamageStructure() = default;

	/**
	* @param affecters Must be Array<IDamageAffecter*>
	*/
	FDamageStructure(const FDamageStructure& base, const TArray<TObjectPtr<class UNetworkObject>>& affecters);

	FDamageStructure(const FDamageStructure& other);

	FDamageStructure& operator = (const FDamageStructure& other);
};

UINTERFACE(BlueprintType)
class UDamageInflictor : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDamageInflictor
{
	GENERATED_BODY()

public:
	IDamageInflictor() = default;

	virtual float calculateTotalDamage() const = 0;

	virtual const TObjectPtr<AController>& getDamageInstigator() const = 0;

	virtual FDamageStructure& getDamage() = 0;

	virtual const FDamageStructure& getDamage() const;
};
