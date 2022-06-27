// Copyright (c) 2021 Use Your Imagination

#include "LoadingScreenInfo.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

#include "Utility/Utility.h"

#pragma warning(disable: 4458)

void ALoadingScreenInfo::BeginPlay()
{
	Super::BeginPlay();

	TArray<TObjectPtr<UUserWidget>> widgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, widgets, loadingScreenClass);

	if (widgets.IsEmpty())
	{
		loadingScreen = NewObject<UUserWidget>(Utility::getGameState(this), loadingScreenClass);

		loadingScreen->AddToViewport();
	}

	onBeginLoadCallback.ExecuteIfBound();
}

void ALoadingScreenInfo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (endCondition.Execute())
	{
		if (deleteLoadingScreenWidget)
		{
			loadingScreen->RemoveFromViewport();
		}

		onEndLoadCallback.ExecuteIfBound();

		Destroy();
	}
}

ALoadingScreenInfo::ALoadingScreenInfo() :
	deleteLoadingScreenWidget(true)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> loadingScreenFinder(TEXT("/Game/UI/UIs/BP_LoadingScreenUI"));

	PrimaryActorTick.bCanEverTick = true;
	bReplicates = false;

	loadingScreenClass = loadingScreenFinder.Class;
}

void ALoadingScreenInfo::setLoadingScreenClass(TSubclassOf<UUserWidget> loadingScreenClass)
{
	this->loadingScreenClass = loadingScreenClass;
}

void ALoadingScreenInfo::setOnBeginLoadCallback(const FCallbackDelegate& onBeginLoadCallback)
{
	this->onBeginLoadCallback = onBeginLoadCallback;
}

void ALoadingScreenInfo::setOnEndLoadCallback(const FCallbackDelegate& onEndLoadCallback)
{
	this->onEndLoadCallback = onEndLoadCallback;
}

void ALoadingScreenInfo::setEndCondition(const FEndConditionDelegate& endCondition)
{
	this->endCondition = endCondition;
}

void ALoadingScreenInfo::setDeleteLoadingScreenWidget(bool deleteLoadingScreenWidget)
{
	this->deleteLoadingScreenWidget = deleteLoadingScreenWidget;
}
