// Copyright (c) 2022 Use-your-imagination

#include "CooldownableUtility.h"

bool UCooldownableUtility::IsSupportedForNetworking() const
{
	return true;
}

void UCooldownableUtility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCooldownableUtility, cooldown);

	DOREPLIFETIME(UCooldownableUtility, currentCooldown);
}

float UCooldownableUtility::getCooldown() const
{
	return cooldown;
}

float& UCooldownableUtility::getCurrentCooldownReference()
{
	return currentCooldown;
}

float UCooldownableUtility::getCurrentCooldown() const
{
	return currentCooldown;
}
