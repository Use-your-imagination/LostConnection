// Copyright (c) 2021 Use-your-imagination

#include "LevelCreationWaypoint.h"

void ALevelCreationWaypoint::BeginPlay()
{
	Super::BeginPlay();
}

ALevelCreationWaypoint::ALevelCreationWaypoint()
{
	PrimaryActorTick.bCanEverTick = false;

	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	arrow->SetArrowColor(FLinearColor::Red);
}
