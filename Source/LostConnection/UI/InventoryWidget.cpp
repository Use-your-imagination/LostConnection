// Copyright (c) 2022 Use-your-imagination

#include "InventoryWidget.h"

#include "Engine/LostConnectionPlayerState.h"

UInventoryWidget* UInventoryWidget::init(ALostConnectionPlayerState* playerState)
{
	inventory = playerState->getInventory();

	return this;
}

void UInventoryWidget::onShow_Implementation()
{

}

void UInventoryWidget::onHide_Implementation()
{

}

void UInventoryWidget::onHideCallback()
{
	this->RemoveFromViewport();

	inventory->getPlayerState()->getCurrentUI()->SetVisibility(ESlateVisibility::Visible);
}
