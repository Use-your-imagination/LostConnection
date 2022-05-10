// Copyright (c) 2021 Use Your Imagination


#include "ReplicationStructures.h"

FAmmoData::FAmmoData(EAmmoType ammoType, int32 ammoCount) :
	ammoCount(ammoCount),
	ammoType(ammoType)
{

}

FCooldownableData::FCooldownableData(float remainingCooldown) :
	remainingCooldown(remainingCooldown)
{

}

FCooldownableAbilitiesData::FCooldownableAbilitiesData(EAbilitySlot slot, float remainingCooldown) :
	FCooldownableData(remainingCooldown),
	slot(slot)
{

}

FCooldownableWeaponsData::FCooldownableWeaponsData(EWeaponSlotType slot, float remainingCooldown) :
	FCooldownableData(remainingCooldown),
	slot(slot)
{

}
