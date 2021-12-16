// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Constants.generated.h"

UCLASS()
class LOSTCONNECTION_API UConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static const FString projectVersion;

	static constexpr float shootDistance = 20000.0f;

	static constexpr int32 actorNetUpdateFrequency = 30;
	static constexpr int32 minNetUpdateFrequency = 1;
	
public:
	UFUNCTION(Category = Constants, BlueprintCallable, BlueprintPure)
	static FText getProjectVersion();
};
