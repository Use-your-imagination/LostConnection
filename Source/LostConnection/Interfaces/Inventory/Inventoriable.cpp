// Copyright (c) 2022 Use Your Imagination

#include "Inventoriable.h"

TArray<FFormatArgumentValue> IInventoriable::getFormatArguments() const
{
	return {};
}

FText IInventoriable::getFormattedItemDescription() const
{
	return FText::Format(this->getItemDescription(), this->getFormatArguments());
}
