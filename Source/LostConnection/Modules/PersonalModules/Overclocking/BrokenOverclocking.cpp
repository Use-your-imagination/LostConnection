// Copyright (c) 2022 Use Your Imagination

#include "BrokenOverclocking.h"

#include "Utility/Utility.h"

bool UBrokenOverclocking::applyCondition(TObjectPtr<AActor> caller) const
{
	if (Utility::checkChanceProc(breakPercent))
	{
		return false;
	}

	return Super::applyCondition(caller);
}
