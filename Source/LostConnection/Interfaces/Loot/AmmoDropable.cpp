// Copyright (c) 2022 Use Your Imagination

#include "AmmoDropable.h"

FTransform IAmmoDropable::getCurrentPosition() const
{
	if (TObjectPtr<AActor> actor = Cast<AActor>(this->_getUObject()))
	{
		return actor->GetActorTransform();
	}

	return {};
}
