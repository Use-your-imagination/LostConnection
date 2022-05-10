// Copyright (c) 2022 Use Your Imagination

#include "TeleportPoint.h"

#include "Utility/Utility.h"
#include "Constants/Constants.h"

void ATeleportPoint::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		room = Utility::getGameState(this)->getLastLoadedRoom();
	}
}

void ATeleportPoint::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATeleportPoint, room);
}

ATeleportPoint::ATeleportPoint()
{
	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
}
