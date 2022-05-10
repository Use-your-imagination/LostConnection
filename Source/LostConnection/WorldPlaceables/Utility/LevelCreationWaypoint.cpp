// Copyright (c) 2021 Use Your Imagination

#include "LevelCreationWaypoint.h"

ALevelCreationWaypoint::ALevelCreationWaypoint()
{
	PrimaryActorTick.bCanEverTick = false;

	arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");

	arrow->SetArrowColor(FLinearColor::Red);
}
