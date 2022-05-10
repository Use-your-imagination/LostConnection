// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "AmmoDropable.generated.h"

UINTERFACE(Blueprintable)
class UAmmoDropable : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IAmmoDropable
{
	GENERATED_BODY()

public:
	IAmmoDropable() = default;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float getSmallAmmoDropChance() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float getLargeAmmoDropChance() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float getEnergyAmmoDropChance() const;

	FTransform getCurrentPosition() const;
};
