// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "Components/CapsuleComponent.h"

#include "DamageReceiver.generated.h"

UINTERFACE(MinimalAPI)
class UDamageReceiver : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDamageReceiver
{
	GENERATED_BODY()

public:
	IDamageReceiver() = default;

	virtual void takeDamage(const TScriptInterface<class IDamageInflictor>& inflictor) = 0;

	virtual float getTotalLifePercentDealt(class IDamageInflictor* inflictor) const = 0;

	virtual float getHealthPercentDealt(class IDamageInflictor* inflictor) const = 0;

	virtual USkeletalMeshComponent* getMeshComponent() = 0;

	virtual UCapsuleComponent* getCapsuleComponent() = 0;
};
