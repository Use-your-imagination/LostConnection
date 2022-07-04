// Copyright (c) 2022 Use Your Imagination

#include "TeleportPoint.h"

#include "Utility/Utility.h"
#include "Constants/Constants.h"

void ATeleportPoint::BeginPlay()
{
	Super::BeginPlay();

	room = Utility::getGameState(this)->getLastLoadedRoom();

	if (this->getNestingLevel() == 0)
	{
		GetWorld()->GetFirstPlayerController<ALostConnectionPlayerController>()->setMainTeleportFromLoadedRoom(this);
	}
}

ATeleportPoint::ATeleportPoint()
{
	bReplicates = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
}

void ATeleportPoint::teleport_Implementation(APlayerController* controller)
{
	TObjectPtr<APawn> pawn = controller->GetPawn();

	if (!IsValid(pawn))
	{
		return;
	}

	pawn->SetActorLocation(GetActorLocation(), false, nullptr, ETeleportType::TeleportPhysics);
}

const TSoftObjectPtr<UWorld>& ATeleportPoint::getRoom() const
{
	return room;
}
