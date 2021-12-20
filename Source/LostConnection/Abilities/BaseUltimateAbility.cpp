// Copyright (c) 2021 Use-your-imagination

#include "BaseUltimateAbility.h"

#include "Characters/BaseCharacter.h"

void UBaseUltimateAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseUltimateAbility, cooldown);

	DOREPLIFETIME(UBaseUltimateAbility, currentCooldown);
}

UBaseUltimateAbility::UBaseUltimateAbility()
{

}

void UBaseUltimateAbility::applyAbility(ABaseCharacter* target)
{
	PURE_VIRTUAL(UBaseUltimateAbility::applyAbility)
}

void UBaseUltimateAbility::useAbility()
{
	this->startCooldown();
}

float UBaseUltimateAbility::getCooldown() const
{
	return cooldown;
}

float& UBaseUltimateAbility::getCurrentCooldown()
{
	return currentCooldown;
}
