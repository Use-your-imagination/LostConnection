// Copyright (c) 2021 Use Your Imagination

#include "AISpawnPoint.h"

AAISpawnPoint::AAISpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");

	arrow->SetArrowColor(FLinearColor::Red);
}

EBotType AAISpawnPoint::getBotSpawnType() const
{
	return botSpawnType;
}
