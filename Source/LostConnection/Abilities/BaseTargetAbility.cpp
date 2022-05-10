// Copyright (c) 2021 Use Your Imagination

#include "BaseTargetAbility.h"

#include "Characters/BaseCharacter.h"

#pragma warning(disable: 4458)

void UBaseTargetAbility::setTarget(const TWeakInterfacePtr<ITarget>& target)
{
	this->target = target;
}

void UBaseTargetAbility::applyAbility(ABaseCharacter* target)
{
	PURE_VIRTUAL(UBaseTargetAbility::applyAbility);
}

void UBaseTargetAbility::useAbility()
{
	PURE_VIRTUAL(UBaseTargetAbility::useAbility);
}
