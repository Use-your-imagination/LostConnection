// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Info.h"
#include "Blueprint/UserWidget.h"

#include "LoadingScreenInfo.generated.h"

DECLARE_DYNAMIC_DELEGATE(FCallbackDelegate);

UCLASS(BlueprintType)
class LOSTCONNECTION_API ALoadingScreenInfo : public AInfo
{
	GENERATED_BODY()
	
private:
	TSubclassOf<UUserWidget> loadingScreenClass;
	FCallbackDelegate onEndLoadCallback;
	FCallbackDelegate onBeginLoadCallback;
	UUserWidget* loadingScreen;

private:
	void BeginPlay() override;
	
	void Tick(float DeltaTime) override;

public:
	ALoadingScreenInfo();

	void setOnBeginLoadCallback(FCallbackDelegate&& onBeginLoadCallback);

	void setOnEndLoadCallback(FCallbackDelegate&& onEndLoadCallback);

	~ALoadingScreenInfo() = default;
};
