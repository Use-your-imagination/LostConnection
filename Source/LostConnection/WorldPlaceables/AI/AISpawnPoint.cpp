// Copyright (c) 2021 Use Your Imagination

#include "AISpawnPoint.h"

AAISpawnPoint::AAISpawnPoint() :
	botSpawnType(EBotType::melee)
{
	PrimaryActorTick.bCanEverTick = false;

	arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");

	arrow->SetArrowColor(FLinearColor::Red);

	SetRootComponent(arrow);
}

EBotType AAISpawnPoint::getBotSpawnType() const
{
	return botSpawnType;
}
