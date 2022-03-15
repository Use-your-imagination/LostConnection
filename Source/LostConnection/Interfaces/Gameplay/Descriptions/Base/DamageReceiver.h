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

	virtual void takeDamageFromInflictor(const TScriptInterface<class IDamageInflictor>& inflictor) = 0;

	void takeDamageFromInflictorHolder(const class IDamageInflictorHolder* inflictorHolder);

	virtual void setCurrentHealth(float newCurrentHealth) = 0;

	virtual float getCurrentHealth() const = 0;

	virtual float getTotalLifePool() const = 0;

	virtual float getLifePool() const = 0;

	virtual float getEnergyShieldPool() const = 0;

	virtual float getTotalLifePercentDealt(class IDamageInflictor* inflictor) const = 0;

	virtual float getLifePercentDealt(class IDamageInflictor* inflictor) const = 0;

	virtual float getEnergyShieldPercentDealt(class IDamageInflictor* inflictor) const = 0;

	float getTotalLifePercentDealt(class IDamageInflictorHolder* inflictorHolder) const;

	float getLifePercentDealt(class IDamageInflictorHolder* inflictorHolder) const;

	float getEnergyShieldPercentDealt(class IDamageInflictorHolder* inflictorHolder) const;

	virtual USkeletalMeshComponent* getMeshComponent() = 0;

	virtual UCapsuleComponent* getCapsuleComponent() = 0;

	template<typename InflictorT>
	float getTotalLifePercentDealt(const TScriptInterface<InflictorT>& inflictor) const;

	template<typename InflictorT>
	float getLifePercentDealt(const TScriptInterface<InflictorT>& inflictor) const;

	template<typename InflictorT>
	float getEnergyShieldPercentDealt(const TScriptInterface<InflictorT>& inflictor) const;
};

template<typename InflictorT>
float IDamageReceiver::getTotalLifePercentDealt(const TScriptInterface<InflictorT>& inflictor) const
{
	static_assert(TIsDerivedFrom<InflictorT, class IDamageInflictor>().IsDerived, "Wrong template type getTotalLifePercentDealt");

	return this->getTotalLifePercentDealt(StaticCast<class IDamageInflictor*>(inflictor.GetInterface()));
}

template<typename InflictorT>
float IDamageReceiver::getLifePercentDealt(const TScriptInterface<InflictorT>& inflictor) const
{
	static_assert(TIsDerivedFrom<InflictorT, class IDamageInflictor>().IsDerived, "Wrong template type getTotalLifePercentDealt");

	return this->getLifePercentDealt(StaticCast<class IDamageInflictor*>(inflictor.GetInterface()));
}

template<typename InflictorT>
float IDamageReceiver::getEnergyShieldPercentDealt(const TScriptInterface<InflictorT>& inflictor) const
{
	static_assert(TIsDerivedFrom<InflictorT, class IDamageInflictor>().IsDerived, "Wrong template type getTotalLifePercentDealt");

	return this->getEnergyShieldPercentDealt(StaticCast<class IDamageInflictor*>(inflictor.GetInterface()));
}
