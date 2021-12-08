// Copyright (c) 2021 Use-your-imagination

#include "AISpawnPoint.h"

AAISpawnPoint::AAISpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	arrow->SetArrowColor(FLinearColor::Red);
}
