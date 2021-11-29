// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/AssetManager.h"

#include "LostConnectionAssetManager.generated.h"

UCLASS()
class LOSTCONNECTION_API ULostConnectionAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	ULostConnectionAssetManager() = default;

	~ULostConnectionAssetManager() = default;
};
