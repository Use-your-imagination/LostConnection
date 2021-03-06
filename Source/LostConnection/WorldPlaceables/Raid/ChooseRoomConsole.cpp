// Copyright (c) 2021 Use Your Imagination

#include "ChooseRoomConsole.h"

#include "Utility/Utility.h"

void AChooseRoomConsole::action(TObjectPtr<ABaseDrone> player)
{
	Utility::getGameState(this)->startRoomLoading();
}

AChooseRoomConsole::AChooseRoomConsole()
{
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");

	mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	mesh->SetGenerateOverlapEvents(true);
}

bool AChooseRoomConsole::isEnable() const
{
	return Utility::getGameState(this)->getRemainingBots() == 0;
}
