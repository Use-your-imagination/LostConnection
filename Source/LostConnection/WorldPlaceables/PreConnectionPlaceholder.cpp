// Copyright (c) 2022 Use-your-imagination

#include "PreConnectionPlaceholder.h"

#include "Constants/Constants.h"
#include "Utility/Utility.h"
#include "Engine/LostConnectionPlayerController.h"
#include "AssetLoading/LostConnectionAssetManager.h"

void APreConnectionPlaceholder::BeginPlay()
{
	Super::BeginPlay();
}

void APreConnectionPlaceholder::Tick_Implementation(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isAlreadySendRespawnRequest)
	{
		return;
	}

	ALostConnectionPlayerController* controller = Cast<ALostConnectionPlayerController>(GetController());
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);

	if (ULostConnectionAssetManager::get().isAssetsLoadingEnd() && IsValid(controller) && IsValid(playerState))
	{
		isAlreadySendRespawnRequest = true;

		playerState->init();

		controller->respawnPlayer();
	}
}

APreConnectionPlaceholder::APreConnectionPlaceholder() :
	isAlreadySendRespawnRequest(false)
{
	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
}
