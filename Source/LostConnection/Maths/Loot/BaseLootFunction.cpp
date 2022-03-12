// Copyright (c) 2022 Use-your-imagination

#include "BaseLootFunction.h"

float UBaseLootFunction::calculateLootChance_Implementation(int32 lootPoints) const
{
	return 0.0f;
}

void UBaseLootFunction::getRange_Implementation(int32& soft, int32& hard) const
{

}

FText UBaseLootFunction::getLootName_Implementation() const
{
	return FText::GetEmpty();
}
