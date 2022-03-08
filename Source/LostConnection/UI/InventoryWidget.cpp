// Copyright (c) 2022 Use-your-imagination

#include "InventoryWidget.h"

#include "Engine/LostConnectionPlayerState.h"

UInventoryWidget* UInventoryWidget::init(ALostConnectionPlayerState* playerState)
{
	inventory = playerState->getInventory();

	return this;
}
