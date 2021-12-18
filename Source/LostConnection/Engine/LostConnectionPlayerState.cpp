// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionPlayerState.h"

void ALostConnectionPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALostConnectionPlayerState, currentUI);
}

void ALostConnectionPlayerState::setCurrentUI_Implementation(UUserWidget* widget)
{
	currentUI = widget;
}

UUserWidget* ALostConnectionPlayerState::getCurrentUI() const
{
	return currentUI;
}
