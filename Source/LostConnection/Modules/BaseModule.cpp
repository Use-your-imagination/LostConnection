// Copyright (c) 2022 Use Your Imagination

#include "BaseModule.h"

const FText& UBaseModule::getItemName() const
{
	return moduleName;
}

const FText& UBaseModule::getItemDescription() const
{
	return moduleDescription;
}

const UTexture2D* UBaseModule::getCellIcon() const
{
	return moduleIconTexture;
}

const FColor& UBaseModule::getBorderColor() const
{
	// TODO: add color to modules

	return FColor::Transparent;
}
