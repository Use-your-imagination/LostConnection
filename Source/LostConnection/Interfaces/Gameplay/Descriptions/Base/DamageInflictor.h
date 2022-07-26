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
	FDamageStructure();

	FDamageStructure(const FDamageStructure& base, const TArray<TScriptInterface<class IDamageAffecter>>& affecters, const TScriptInterface<class IDamageInflictor>& inflictor, const TScriptInterface<class IDamageReceiver>& receiver);

	FDamageStructure(const FDamageStructure& other);

	FDamageStructure& operator = (const FDamageStructure& other);

	~FDamageStructure() = default;
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

	/**
	* @param receiver Can be nullptr
	*/
	virtual float calculateTotalDamage(const TScriptInterface<class IDamageReceiver>& receiver = nullptr) const = 0;

	virtual const TObjectPtr<AController>& getDamageInstigator() const = 0;

	virtual FDamageStructure& getDamage() = 0;

	virtual const FDamageStructure& getDamage() const;
};
