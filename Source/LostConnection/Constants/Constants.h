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

	static constexpr int32 actorNetUpdateFrequency = 45;
	static constexpr int32 minNetUpdateFrequency = 1;
	
	static constexpr int32 defaultSmallAmmoMaxCount = 700;
	static constexpr int32 defaultLargeAmmoMaxCount = 240;
	static constexpr int32 defaultEnergyAmmoMaxCount = 50;

	/// @brief Convert max ammo count to default ammo count
	static constexpr float conversionAmmoCoefficient = 1.0f;

	static constexpr float showHealthBarDistance = 5000.0f;

public:
	static const FName actionStringTablePath;
	static const FString defaultActionMessageKey;
	static const FString actionHotkey;

public:
	UFUNCTION(Category = Constants, BlueprintCallable, BlueprintPure)
	static FText getProjectVersion();
};
