// Copyright (c) 2021 Use-your-imagination

#include "LevelCreationWaypoint.h"

ALevelCreationWaypoint::ALevelCreationWaypoint()
{
	PrimaryActorTick.bCanEverTick = false;

	arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");

	arrow->SetArrowColor(FLinearColor::Red);
}
