// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionPlayerState.h"

void ALostConnectionPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

UUserWidget* ALostConnectionPlayerState::setCurrentUI(UUserWidget* widget)
{
	currentUI = widget;

	return currentUI;
}

UUserWidget* ALostConnectionPlayerState::getCurrentUI() const
{
	return currentUI;
}
