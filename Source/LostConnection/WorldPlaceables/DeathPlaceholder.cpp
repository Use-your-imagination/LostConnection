// Copyright (c) 2021 Use-your-imagination

#include "DeathPlaceholder.h"

#include "Kismet/GameplayStatics.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "Utility/Utility.h"
#include "Utility/MultiplayerUtility.h"

void ADeathPlaceholder::checkRespawn()
{
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);

	if (playerState->getCurrentRespawnCooldown())
	{
		return;
	}

	playerState->resetCurrentUI();

	Utility::getPlayerController(this)->respawnPlayer(GetActorTransform());
}

void ADeathPlaceholder::BeginPlay()
{
	Super::BeginPlay();

	Utility::executeOnOwningClient(this, [this]()
		{
			Utility::setCurrentUI(ULostConnectionAssetManager::get().getUI().getDefaultDeathUI(), this);
		});
}

void ADeathPlaceholder::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	FInputActionBinding action("Action", IE_Pressed);

	action.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			MultiplayerUtility::runOnServerReliable(this, "checkRespawn");
		});

	PlayerInputComponent->AddActionBinding(action);
}
