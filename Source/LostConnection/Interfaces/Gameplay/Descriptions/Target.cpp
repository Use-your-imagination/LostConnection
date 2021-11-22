// Copyright (c) 2021 Use-your-imagination

#include "Target.h"

#include "Characters/BaseCharacter.h"

#pragma warning(disable: 4458)

void ITarget::setObjectTarget(ABaseCharacter* objectTarget)
{
	this->objectTarget = objectTarget;
}

void ITarget::setPositionTarget(const FVector& positionTarget)
{
	this->positionTarget = positionTarget;
}

void ITarget::setEnvironmentTarget(const TScriptInterface<IEnvironmentTarget>& environmentTarget)
{
	this->environmentTarget = environmentTarget;
}

TWeakObjectPtr<ABaseCharacter>& ITarget::getObjectTarget()
{
	return objectTarget;
}

const FVector& ITarget::getPositionTarget() const
{
	return positionTarget;
}

TWeakInterfacePtr<IEnvironmentTarget>& ITarget::getEnvironmentTarget()
{
	return environmentTarget;
}
