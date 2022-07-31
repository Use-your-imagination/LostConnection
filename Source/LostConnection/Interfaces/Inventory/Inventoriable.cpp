// Copyright (c) 2022 Use Your Imagination

#include "Inventoriable.h"

TArray<FFormatArgumentValue> IInventoriable::getFormatArguments() const
{
	return {};
}

void IInventoriable::equip()
{
	this->getIsEquipped() = true;
}

void IInventoriable::unequip()
{
	this->getIsEquipped() = false;
}

FText IInventoriable::getFormattedItemDescription() const
{
	return FText::Format(this->getItemDescription(), this->getFormatArguments());
}

bool IInventoriable::isEquipped() const
{
	return const_cast<IInventoriable*>(this)->getIsEquipped();
}
