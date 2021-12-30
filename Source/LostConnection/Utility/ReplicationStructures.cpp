// Copyright (c) 2021 Use-your-imagination


#include "ReplicationStructures.h"

FAmmoData::FAmmoData(ammoTypes ammoType, int32 ammoCount) :
	ammoCount(ammoCount),
	ammoType(ammoType)
{

}

FCooldownableData::FCooldownableData(float remainingCooldown) :
	remainingCooldown(remainingCooldown)
{

}

FCooldownableAbilitiesData::FCooldownableAbilitiesData(abilitySlot slot, float remainingCooldown) :
	FCooldownableData(remainingCooldown),
	slot(slot)
{

}

FCooldownableWeaponsData::FCooldownableWeaponsData(weaponSlotTypes slot, float remainingCooldown) :
	FCooldownableData(remainingCooldown),
	slot(slot)
{

}
