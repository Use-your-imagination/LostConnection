// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "Components/CapsuleComponent.h"

#include "DamageReceiver.generated.h"

UINTERFACE(BlueprintType)
class UDamageReceiver : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDamageReceiver
{
	GENERATED_BODY()

public:
	IDamageReceiver() = default;

	virtual void takeDamageFromInflictor(const TScriptInterface<class IDamageInflictor>& inflictor) = 0;

	void takeDamageFromInflictorHolder(const TScriptInterface<class IDamageInflictorHolder>& inflictorHolder);

	virtual void setCurrentHealth(float newCurrentHealth) = 0;

	virtual float getCurrentHealth() const = 0;

	virtual float getTotalLifePool() const = 0;

	virtual float getLifePool() const = 0;

	virtual float getEnergyShieldPool() const = 0;

	virtual float getTotalLifePercentDealt(const TScriptInterface<class IDamageInflictor>& inflictor) const = 0;

	virtual float getLifePercentDealt(const TScriptInterface<class IDamageInflictor>& inflictor) const = 0;

	virtual float getEnergyShieldPercentDealt(const TScriptInterface<class IDamageInflictor>& inflictor) const = 0;

	virtual USkeletalMeshComponent* getMeshComponent() = 0;

	virtual UCapsuleComponent* getCapsuleComponent() = 0;
};
