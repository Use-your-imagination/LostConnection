// Copyright (c) 2022 Use Your Imagination

#include "InventoryWidget.h"

#include "Engine/LostConnectionPlayerState.h"

void UInventoryWidget::init(TObjectPtr<ALostConnectionPlayerState> playerState)
{
	Super::init(playerState);

	inventory = playerState->getInventory();
}

void UInventoryWidget::onShow_Implementation()
{
	inventory->getPlayerState()->addEscapableWidget(this);
}

void UInventoryWidget::onHide_Implementation()
{

}

void UInventoryWidget::onHideCallback()
{
	inventory->getPlayerState()->popEscapableWidget();
}
