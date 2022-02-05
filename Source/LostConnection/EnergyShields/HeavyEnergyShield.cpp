// Copyright (c) 2022 Use-your-imagination

#include "HeavyEnergyShield.h"

void UHeavyEnergyShield::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHeavyEnergyShield, basePoolConversion);

	DOREPLIFETIME(UHeavyEnergyShield, poolRechargeRate);

	DOREPLIFETIME(UHeavyEnergyShield, poolCapacity);

	DOREPLIFETIME(UHeavyEnergyShield, currentPoolCapacity);
}

float UHeavyEnergyShield::getBasePoolConversion() const
{
	return basePoolConversion;
}

float UHeavyEnergyShield::getPoolRechargeRate() const
{
	return poolRechargeRate;
}

float UHeavyEnergyShield::getPoolCapacity() const
{
	return poolCapacity;
}

float UHeavyEnergyShield::getCurrentPoolCapacity() const
{
	return currentPoolCapacity;
}

void UHeavyEnergyShield::init()
{
	Super::init();

	poolCapacity = capacity * Utility::fromPercent(basePoolConversion);
	currentPoolCapacity = poolCapacity;

	capacity -= poolCapacity;
	currentCapacity = capacity;

	timers.addTimer([this]()
		{
			if (isRecharging)
			{
				currentPoolCapacity = FMath::Min(poolCapacity, currentPoolCapacity + currentPoolCapacity * Utility::fromPercent(poolRechargeRate));
			}
		}, 1.0f);
}
