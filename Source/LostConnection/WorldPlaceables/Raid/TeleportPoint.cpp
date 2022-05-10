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

		if (this->getNestingLevel() == 0)
		{
			TArray<TObjectPtr<AActor>> controllers;

			UGameplayStatics::GetAllActorsOfClass(this, ALostConnectionPlayerController::StaticClass(), controllers);

			for (TObjectPtr<AActor> controller : controllers)
			{
				this->teleport(Cast<APlayerController>(controller));
			}
		}
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

void ATeleportPoint::teleport_Implementation(APlayerController* controller)
{
	TObjectPtr<APawn> pawn = controller->GetPawn();

	if (!IsValid(pawn))
	{
		return;
	}

	pawn->SetActorLocation(GetActorLocation());
}

const TSoftObjectPtr<UWorld>& ATeleportPoint::getRoom() const
{
	return room;
}
