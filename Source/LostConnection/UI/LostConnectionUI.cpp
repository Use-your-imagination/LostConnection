// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionUI.h"

#include "Characters/BaseDrone.h"

ULostConnectionUI::ULostConnectionUI(const FObjectInitializer& objectInitializer) :
	UUserWidget(objectInitializer)
{

}

void ULostConnectionUI::init(ABaseDrone* player)
{
	this->player = player;

	this->UIConstruction();
}

void ULostConnectionUI::UIConstruction_Implementation()
{

}
