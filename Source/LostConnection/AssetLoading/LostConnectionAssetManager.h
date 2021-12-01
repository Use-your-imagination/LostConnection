// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/AssetManager.h"

#include "AssetsCollection.h"

#include "LostConnectionAssetManager.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API ULostConnectionAssetManager : public UAssetManager
{
	GENERATED_BODY()

private:
	AssetsCollection& assets = AssetsCollection::get();

private:
	TSharedPtr<FStreamableHandle> statuses;

public:
	ULostConnectionAssetManager() = default;

	UFUNCTION(BlueprintCallable)
	void loadStatuses();

	~ULostConnectionAssetManager() = default;
};
