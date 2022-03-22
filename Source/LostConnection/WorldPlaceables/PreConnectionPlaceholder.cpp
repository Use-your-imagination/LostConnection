// Copyright (c) 2022 Use-your-imagination

#include "PreConnectionPlaceholder.h"

#include "Constants/Constants.h"
#include "Utility/Utility.h"
#include "Engine/LostConnectionPlayerController.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "Characters/Drones/SN4K3/SN4K3.h"

void APreConnectionPlaceholder::Tick_Implementation(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isAlreadySendRespawnRequest || !GetController())
	{
		return;
	}

	ALostConnectionPlayerController* playerController = GetController<ALostConnectionPlayerController>();
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);

	if (ULostConnectionAssetManager::get().isAssetsLoadingEnd() && IsValid(playerController) && IsValid(playerState))
	{
		isAlreadySendRespawnRequest = true;

		playerState->setDroneClass(ASN4K3::StaticClass());

		playerState->setPlayerController(playerController);

		playerState->init();

		playerController->respawnPlayer(playerController->GetPawn()->GetActorTransform());

		playerState->setCurrentRespawnCooldown(0.0f);
	}
}

APreConnectionPlaceholder::APreConnectionPlaceholder() :
	isAlreadySendRespawnRequest(false)
{
	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
}
