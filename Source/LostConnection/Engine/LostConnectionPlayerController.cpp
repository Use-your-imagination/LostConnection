// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionPlayerController.h"

#include "Constants/Constants.h"

void ALostConnectionPlayerController::GetSeamlessTravelActorList(bool bToEntry, TArray<AActor*>& ActorList)
{
	ActorList.Add(GetPawn());

	Super::GetSeamlessTravelActorList(bToEntry, ActorList);
}

ALostConnectionPlayerController::ALostConnectionPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
}
