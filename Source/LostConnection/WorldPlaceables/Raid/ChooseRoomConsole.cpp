// Copyright (c) 2021 Use-your-imagination

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
	return !StaticCast<bool>(Utility::getGameState(this)->getRemainingBots());
}
