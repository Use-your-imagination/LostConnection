// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "BaseDroneDataAsset.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API UBaseDroneDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UBaseDroneDataAsset() = default;

	virtual ~UBaseDroneDataAsset() = default;
};
