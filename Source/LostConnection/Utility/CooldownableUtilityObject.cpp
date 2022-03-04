// Copyright (c) 2022 Use-your-imagination

#include "CooldownableUtilityObject.h"

bool UCooldownableUtilityObject::IsSupportedForNetworking() const
{
	return true;
}

void UCooldownableUtilityObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCooldownableUtilityObject, cooldown);

	DOREPLIFETIME(UCooldownableUtilityObject, currentCooldown);
}

float UCooldownableUtilityObject::getCooldown() const
{
	return cooldown;
}

float& UCooldownableUtilityObject::getCurrentCooldownReference()
{
	return currentCooldown;
}

float UCooldownableUtilityObject::getCurrentCooldown() const
{
	return currentCooldown;
}
