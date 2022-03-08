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
	FInputActionBinding action("Action", IE_Pressed);
	FInputActionBinding inventory("Inventory", IE_Pressed);

	action.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			MultiplayerUtility::runOnServerReliable(this, "checkRespawn");
		});

	inventory.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);

			if (!playerState)
			{
				return;
			}

			UUserWidget* currentUI = playerState->getCurrentUI();
			
			if (IInventoryUIHolder::Execute_getInventoryWidget(currentUI)->IsInViewport())
			{
				IInventoryUIHolder::Execute_hideInventory(currentUI, Utility::getPlayerController(this));
			}
			else
			{
				IInventoryUIHolder::Execute_showInventory(currentUI, Utility::getPlayerController(this));
			}
		});

	PlayerInputComponent->AddActionBinding(action);

	PlayerInputComponent->AddActionBinding(inventory);
}
