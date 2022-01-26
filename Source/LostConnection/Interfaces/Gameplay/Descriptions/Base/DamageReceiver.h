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

	virtual float getTotalLifePool() const = 0;

	virtual float getTotalLifePercentDealt(class IDamageInflictor* inflictor) const = 0;

	virtual USkeletalMeshComponent* getMeshComponent() = 0;

	virtual UCapsuleComponent* getCapsuleComponent() = 0;

	template<typename InflictorT>
	float getTotalLifePercentDealt(const TScriptInterface<InflictorT>& inflictor) const;
};

template<typename InflictorT>
float IDamageReceiver::getTotalLifePercentDealt(const TScriptInterface<InflictorT>& inflictor) const
{
	static_assert(TIsDerivedFrom<InflictorT, class IDamageInflictor>().IsDerived, "Wrong template type getTotalLifePercentDealt");

	return this->getTotalLifePercentDealt(StaticCast<class IDamageInflictor*>(inflictor.GetInterface()));
}
