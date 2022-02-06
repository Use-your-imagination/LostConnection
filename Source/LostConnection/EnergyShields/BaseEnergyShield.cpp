// Copyright (c) 2022 Use-your-imagination

#include "BaseEnergyShield.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

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

void UBaseEnergyShield::init(float startEnergyShieldCapacity)
{
	capacity = startEnergyShieldCapacity;
	currentCapacity = startEnergyShieldCapacity;

	timers.addTimer([this]()
		{
			if (isRecharging)
			{
				currentCapacity = FMath::Min(capacity, currentCapacity + currentCapacity * Utility::fromPercent(rechargeRate));

				if (currentCapacity == capacity)
				{
					this->onEndRechargeShield();
				}
			}
		}, 1.0f);
}

float UBaseEnergyShield::takeDamage(const TScriptInterface<IDamageInflictor>& inflictor)
{
	currentCapacity -= inflictor->calculateTotalDamage();

	if (currentCapacity <= 0)
	{
		this->onDestroyShield();

		return FMath::Abs(currentCapacity);
	}

	return 0;
}

void UBaseEnergyShield::restoreShield_Implementation()
{
	this->onStartRechargeShield();
}

void UBaseEnergyShield::onDestroyShield()
{
	remainingTimeToRestoreShield = rechargeDelay;

	isRecharging = false;
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

float UBaseEnergyShield::getCapacity() const
{
	return capacity;
}

float UBaseEnergyShield::getCurrentCapacity() const
{
	return currentCapacity;
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
