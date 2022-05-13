// Copyright (c) 2022 Use Your Imagination

#include "BaseGrappleHandler.h"

#include "Characters/BaseDrone.h"

void UBaseGrappleHandler::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseGrappleHandler, grappleClass);
}

void UBaseGrappleHandler::init(TObjectPtr<ABaseDrone> drone)
{
	this->drone = drone;
}

UWorld* UBaseGrappleHandler::GetWorld() const
{
	return IsValid(drone) ? drone->GetWorld() : nullptr;
}
