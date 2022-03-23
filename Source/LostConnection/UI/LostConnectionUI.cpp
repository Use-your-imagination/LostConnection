// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionUI.h"

#include "Characters/BaseDrone.h"
#include "Utility/Utility.h"

void ULostConnectionUI::init(ABaseDrone* player)
{
	this->player = player;

	this->UIConstruction();

	inventoryWidget = CreateWidget<UInventoryWidget>(Utility::getPlayerController(player), ULostConnectionAssetManager::get().getUI().getInventoryWidget());

	inventoryWidget->init(Utility::getPlayerState(player));
}

void ULostConnectionUI::UIConstruction_Implementation()
{

}

void ULostConnectionUI::onEnergyShieldUpdate_Implementation()
{

}

void ULostConnectionUI::setPlayer_Implementation(APawn* playerPawn)
{
	player = Cast<ABaseDrone>(playerPawn);
}

APawn* ULostConnectionUI::getPlayer_Implementation() const
{
	return player;
}

UInventoryWidget* ULostConnectionUI::getInventoryWidget_Implementation() const
{
	return inventoryWidget;
}
