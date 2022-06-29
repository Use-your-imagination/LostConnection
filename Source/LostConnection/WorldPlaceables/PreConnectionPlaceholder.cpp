// Copyright (c) 2022 Use Your Imagination

#include "PreConnectionPlaceholder.h"

#include "Constants/Constants.h"
#include "Utility/Utility.h"
#include "Engine/LostConnectionPlayerController.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "Characters/Drones/SN4K3/SN4K3.h"

void APreConnectionPlaceholder::Tick_Implementation(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (isAlreadySendRespawnRequest || !GetController())
	{
		return;
	}

	static ULostConnectionAssetManager& manager = ULostConnectionAssetManager::get();
	TObjectPtr<ALostConnectionPlayerController> playerController = GetController<ALostConnectionPlayerController>();
	TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this);

	if (manager.isAssetsLoadingEnd() && playerController && playerState)
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
