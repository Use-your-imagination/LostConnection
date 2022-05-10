// Copyright (c) 2021 Use Your Imagination

#include "BaseUltimateAbility.h"

#include "Characters/BaseCharacter.h"

void UBaseUltimateAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseUltimateAbility, cooldown);
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
	return cooldown->getCooldown();
}

float& UBaseUltimateAbility::getCurrentCooldownReference()
{
	return cooldown->getCurrentCooldownReference();
}

float UBaseUltimateAbility::getCurrentCooldown() const
{
	return cooldown->getCurrentCooldown();
}

bool UBaseUltimateAbility::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(cooldown, *Bunch, *RepFlags);

	return wroteSomething;
}
