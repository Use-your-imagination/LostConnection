// Copyright (c) 2022 Use-your-imagination

#include "BaseEnergyShield.h"

void UBaseEnergyShield::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseEnergyShield, capacity);

	DOREPLIFETIME(UBaseEnergyShield, rechargeDelay);

	DOREPLIFETIME(UBaseEnergyShield, rechargeRate);

	DOREPLIFETIME(UBaseEnergyShield, addedEffectiveness);

	DOREPLIFETIME(UBaseEnergyShield, remainingTimeToRestoreShield);
}

void UBaseEnergyShield::restoreShield_Implementation()
{
	this->onRestoreShield();
}

void UBaseEnergyShield::onDestroyShield()
{
	remainingTimeToRestoreShield = rechargeDelay;
}

void UBaseEnergyShield::onRestoreShield()
{

}

void UBaseEnergyShield::Tick(float DeltaTime)
{
	if (remainingTimeToRestoreShield)
	{
		remainingTimeToRestoreShield = FMath::Max(0.0f, remainingTimeToRestoreShield - DeltaTime);

		if (!remainingTimeToRestoreShield)
		{
			this->restoreShield();
		}
	}
}
