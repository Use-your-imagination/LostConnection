// Copyright (c) 2022 Use Your Imagination

#include "PlatinumOverclocking.h"

#include "Utility/Utility.h"

TArray<FFormatArgumentValue> UPlatinumOverclocking::getFormatArguments() const
{
	TArray<FFormatArgumentValue> values = Super::getFormatArguments();

	values.Add(Utility::fromPercent(moreDamageCoefficient));

	values.Add(duration);

	return values;
}

void UPlatinumOverclocking::uniqueAction_Implementation(AActor* caller)
{
	// TODO: add more damage
}
