// Copyright (c) 2022 Use Your Imagination

#include "UtilityStructures.h"

FStatDescription::FStatDescription(const FText& name, float value, const FText& nameTooltip, const FText& valueTooltip) :
	name(name),
	value(value),
	nameTooltip(nameTooltip),
	valueTooltip(valueTooltip)
{

}
