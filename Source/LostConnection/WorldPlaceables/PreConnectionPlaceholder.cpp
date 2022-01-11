// Copyright (c) 2022 Use-your-imagination

#include "PreConnectionPlaceholder.h"

#include "Constants/Constants.h"

void APreConnectionPlaceholder::BeginPlay()
{
	Super::BeginPlay();
}

APreConnectionPlaceholder::APreConnectionPlaceholder()
{
	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
}
