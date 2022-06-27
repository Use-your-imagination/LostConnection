// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Info.h"
#include "Blueprint/UserWidget.h"

#include "LoadingScreenInfo.generated.h"

DECLARE_DYNAMIC_DELEGATE(FCallbackDelegate);

DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FEndConditionDelegate);

UCLASS(BlueprintType)
class LOSTCONNECTION_API ALoadingScreenInfo : public AInfo
{
	GENERATED_BODY()
	
private:
	TSubclassOf<UUserWidget> loadingScreenClass;
	FCallbackDelegate onEndLoadCallback;
	FCallbackDelegate onBeginLoadCallback;
	FEndConditionDelegate endCondition;
	bool deleteLoadingScreenWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> loadingScreen;

private:
	void BeginPlay() override;
	
	void Tick(float DeltaTime) override;

public:
	ALoadingScreenInfo();

	void setLoadingScreenClass(TSubclassOf<UUserWidget> loadingScreenClass);

	void setOnBeginLoadCallback(const FCallbackDelegate& onBeginLoadCallback);

	void setOnEndLoadCallback(const FCallbackDelegate& onEndLoadCallback);

	void setEndCondition(const FEndConditionDelegate& endCondition);

	void setDeleteLoadingScreenWidget(bool deleteLoadingScreenWidget);

	~ALoadingScreenInfo() = default;
};
