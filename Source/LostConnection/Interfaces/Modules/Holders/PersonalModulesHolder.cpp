// Copyright (c) 2021 Use Your Imagination

#include "PersonalModulesHolder.h"

#include "Utility/Utility.h"

void IPersonalModulesHolder::addPersonalModule(TObjectPtr<UBasePersonalModule> module)
{
	Utility::getPlayerState(Cast<APawn>(this->_getUObject()))->addPersonalModule(module);
}
