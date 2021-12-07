// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionPlayerController.h"

void ALostConnectionPlayerController::GetSeamlessTravelActorList(bool bToEntry, TArray<AActor*>& ActorList)
{
	Super::GetSeamlessTravelActorList(bToEntry, ActorList);

	ActorList.Add(GetPawn());
}

ALostConnectionPlayerController::ALostConnectionPlayerController()
{
	NetUpdateFrequency = 60;
}
