// Copyright (c) 2022 Use Your Imagination

#include "PlatinumPowderHeavy.h"

#include "Utility/Utility.h"

TArray<FFormatArgumentValue> UPlatinumPowderHeavy::getFormatArguments() const
{
	TArray<FFormatArgumentValue> values = Super::getFormatArguments();

	values.Add(Utility::fromPercent(moreDamageCoefficient));

	values.Add(duration);

	return values;
}

void UPlatinumPowderHeavy::uniqueAction_Implementation(AActor* caller)
{
	// TODO: add more damage
}
