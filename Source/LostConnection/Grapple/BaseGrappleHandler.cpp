// Copyright (c) 2022 Use Your Imagination

#include "BaseGrappleHandler.h"

#include "Characters/BaseDrone.h"

void UBaseGrappleHandler::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseGrappleHandler, grappleClass);

	DOREPLIFETIME(UBaseGrappleHandler, cooldown);
}

void UBaseGrappleHandler::init(TObjectPtr<ABaseDrone> drone)
{
	this->drone = drone;
}

bool UBaseGrappleHandler::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(cooldown, *Bunch, *RepFlags);

	return wroteSomething;
}

UWorld* UBaseGrappleHandler::GetWorld() const
{
	return IsValid(drone) ? drone->GetWorld() : nullptr;
}

float UBaseGrappleHandler::getCooldown() const
{
	return cooldown->getCooldown();
}

float& UBaseGrappleHandler::getCurrentCooldownReference()
{
	return cooldown->getCurrentCooldownReference();
}

float UBaseGrappleHandler::getCurrentCooldown() const
{
	return cooldown->getCurrentCooldown();
}
