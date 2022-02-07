// Copyright (c) 2022 Use-your-imagination

#include "BaseEnergyShield.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"
#include "Characters/BaseCharacter.h"

void UBaseEnergyShield::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseEnergyShield, capacity);

	DOREPLIFETIME(UBaseEnergyShield, currentCapacity);

	DOREPLIFETIME(UBaseEnergyShield, rechargeDelay);

	DOREPLIFETIME(UBaseEnergyShield, rechargeRate);

	DOREPLIFETIME(UBaseEnergyShield, addedEffectiveness);

	DOREPLIFETIME(UBaseEnergyShield, remainingTimeToRestoreShield);

	DOREPLIFETIME(UBaseEnergyShield, isRecharging);
}

void UBaseEnergyShield::onCurrentCapacityChanged()
{
	owner->onCurrentHealthChange();
}

void UBaseEnergyShield::startRechargeDelay()
{
	remainingTimeToRestoreShield = rechargeDelay;

	isRecharging = false;
}

void UBaseEnergyShield::init(const TWeakObjectPtr<ABaseCharacter>& owner)
{
	this->owner = owner;

	capacity = owner->getStartEnergyShieldCapacity();
	currentCapacity = capacity;

	timers.addTimer([this]()
		{
			if (isRecharging)
			{
				currentCapacity = FMath::Min(capacity, currentCapacity + capacity * Utility::fromPercent(rechargeRate));

				if (currentCapacity == capacity)
				{
					this->onEndRechargeShield();
				}
			}
		}, 1.0f);
}

float UBaseEnergyShield::takeDamage(const TScriptInterface<IDamageInflictor>& inflictor)
{
	float tem = currentCapacity - inflictor->calculateTotalDamage();
	float remainingDamage = 0.0f;

	if (tem <= 0)
	{
		remainingDamage = FMath::Abs(tem);

		currentCapacity = 0.0f;

		this->onDestroyShield();
	}
	else
	{
		currentCapacity = tem;
	}

	this->startRechargeDelay();

	this->onCurrentCapacityChanged();

	return remainingDamage;
}

void UBaseEnergyShield::restoreShield_Implementation()
{
	this->onStartRechargeShield();
}

void UBaseEnergyShield::onDestroyShield()
{
	this->startRechargeDelay();
}

void UBaseEnergyShield::onStartRechargeShield()
{
	isRecharging = true;
}

void UBaseEnergyShield::onEndRechargeShield()
{
	isRecharging = false;
}

void UBaseEnergyShield::Tick(float DeltaTime)
{
	timers.processTimers(DeltaTime);

	if (remainingTimeToRestoreShield)
	{
		remainingTimeToRestoreShield = FMath::Max(0.0f, remainingTimeToRestoreShield - DeltaTime);

		if (!remainingTimeToRestoreShield)
		{
			this->restoreShield();
		}
	}
}

const FLinearColor& UBaseEnergyShield::getEnergyShieldColor() const
{
	return energyShieldColor;
}

float UBaseEnergyShield::getRechargeDelay() const
{
	return rechargeDelay;
}

float UBaseEnergyShield::getAddedEffectiveness() const
{
	return addedEffectiveness;
}

float UBaseEnergyShield::getRemainingTimeToRestoreShield() const
{
	return remainingTimeToRestoreShield;
}

bool UBaseEnergyShield::getIsRecharging() const
{
	return isRecharging;
}
