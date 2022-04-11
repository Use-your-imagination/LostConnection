// Copyright (c) 2022 Use-your-imagination

#include "BaseDroppedAmmo.h"

ABaseDroppedAmmo::ABaseDroppedAmmo()
{
	pickupArea = CreateDefaultSubobject<USphereComponent>("PickupArea");
}
