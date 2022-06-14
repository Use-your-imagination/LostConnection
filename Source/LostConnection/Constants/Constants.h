// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Utility/Enums.h"

#include "Constants.generated.h"

UCLASS()
class LOSTCONNECTION_API UConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static constexpr float crouchMaxWalkSpeedCoefficient = 3.0f;
	static constexpr float jumpVelocity = 600.0f;
	static const FRotator rotationRate;

	static constexpr int32 actorNetUpdateFrequency = 60;
	static constexpr int32 minNetUpdateFrequency = 1;
	
	static constexpr float ammoSpeed = 5200.0f;

	static constexpr float showHealthBarDistance = 5000.0f;

	static constexpr int32 startZOrder = 1000;

	static constexpr ECollisionChannel shotThroughChannel = ECollisionChannel::ECC_GameTraceChannel1;
	static constexpr ECollisionChannel droneInteractiveChannel = ECollisionChannel::ECC_GameTraceChannel2;

public:
	static const FName actionStringTablePath;
	static const FString defaultActionMessageKey;
	static const FString actionHotkey;

public:
	UFUNCTION(Category = Constants, BlueprintCallable, BlueprintPure)
	static FText getProjectVersion();

	UFUNCTION(Category = Constants, BlueprintCallable, BlueprintPure)
	static int32 getWeaponModulesSize(EWeaponRarity rarity);
};
