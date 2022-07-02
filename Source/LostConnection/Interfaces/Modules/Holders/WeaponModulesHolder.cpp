// Copyright (c) 2021 Use Your Imagination

#include "WeaponModulesHolder.h"

#include "Utility/Utility.h"

void IWeaponModulesHolder::addWeaponModule(TObjectPtr<UBaseWeaponModule> module)
{
	Utility::getPlayerState(Cast<APawn>(this->_getUObject()))->addWeaponModule(module);
}
