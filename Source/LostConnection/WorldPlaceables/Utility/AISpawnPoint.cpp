// Copyright (c) 2021 Use-your-imagination

#include "AISpawnPoint.h"

AAISpawnPoint::AAISpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");

	arrow->SetArrowColor(FLinearColor::Red);
}
