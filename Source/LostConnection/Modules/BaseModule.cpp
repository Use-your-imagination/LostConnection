// Copyright (c) 2022 Use-your-imagination


#include "BaseModule.h"

const FText& UBaseModule::getItemName() const
{
	return moduleName;
}

const FText& UBaseModule::getItemDescription() const
{
	return moduleDescription;
}
