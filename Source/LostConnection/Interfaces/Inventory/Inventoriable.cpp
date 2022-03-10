// Copyright (c) 2022 Use-your-imagination

#include "Inventoriable.h"

UNetworkObject* IInventoriable::getObject() const
{
	return CastChecked<UNetworkObject>(_getUObject());
}
