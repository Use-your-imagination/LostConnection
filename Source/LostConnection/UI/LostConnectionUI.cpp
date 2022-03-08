// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionUI.h"

#include "Characters/BaseDrone.h"
#include "Utility/Blueprints/UtilityBlueprintFunctionLibrary.h"

ULostConnectionUI::ULostConnectionUI(const FObjectInitializer& objectInitializer) :
	UUserWidget(objectInitializer)
{
	
}

void ULostConnectionUI::init(ABaseDrone* player)
{
	this->player = player;

	this->UIConstruction();

	inventoryWidget = UUtilityBlueprintFunctionLibrary::makeDefaultInventoryWidget(player->GetController<APlayerController>(), this);
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
