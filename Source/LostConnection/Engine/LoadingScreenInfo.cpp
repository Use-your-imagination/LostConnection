// Copyright (c) 2021 Use-your-imagination

#include "LoadingScreenInfo.h"

#include "AssetLoading/LostConnectionAssetManager.h"

#pragma warning(disable: 4458)

void ALoadingScreenInfo::BeginPlay()
{
	Super::BeginPlay();

	loadingScreen = NewObject<UUserWidget>(this, loadingScreenClass);

	loadingScreen->AddToViewport();

	onBeginLoadCallback.ExecuteIfBound();
}

void ALoadingScreenInfo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ULostConnectionAssetManager& manager = ULostConnectionAssetManager::get();

	if (manager.getCurrentPercentLoading() == 100.0f)
	{
		loadingScreen->RemoveFromViewport();

		onEndLoadCallback.ExecuteIfBound();

		Destroy();
	}
}

ALoadingScreenInfo::ALoadingScreenInfo()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> loadingScreenFinder(TEXT("/Game/LoadingScreen/BP_LoadingScreenUI"));

	PrimaryActorTick.bCanEverTick = true;

	loadingScreenClass = loadingScreenFinder.Class;
}

void ALoadingScreenInfo::setOnBeginLoadCallback(FCallbackDelegate&& onBeginLoadCallback)
{
	this->onBeginLoadCallback = MoveTemp(onBeginLoadCallback);
}

void ALoadingScreenInfo::setOnEndLoadCallback(FCallbackDelegate&& onEndLoadCallback)
{
	this->onEndLoadCallback = MoveTemp(onEndLoadCallback);
}