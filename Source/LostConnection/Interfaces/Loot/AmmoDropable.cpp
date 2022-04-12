// Copyright (c) 2022 Use-your-imagination

#include "AmmoDropable.h"

FTransform IAmmoDropable::getCurrentPosition()
{
	if (TObjectPtr<AActor> actor = Cast<AActor>(this->_getUObject()))
	{
		return actor->GetActorTransform();
	}

	return {};
}
