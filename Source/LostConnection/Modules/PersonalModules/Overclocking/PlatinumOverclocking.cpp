// Copyright (c) 2022 Use Your Imagination

#include "PlatinumOverclocking.h"

void UPlatinumOverclocking::uniqueAction(TObjectPtr<AActor> caller)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Unique action"));
}
