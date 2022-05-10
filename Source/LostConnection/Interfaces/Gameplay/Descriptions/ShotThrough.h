// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "ShotThrough.generated.h"

UINTERFACE(Blueprintable)
class UShotThrough : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IShotThrough
{
	GENERATED_BODY()

public:
	IShotThrough() = default;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float getFlatDamageReduction() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float getPercentageDamageReduction() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void impactAction(class AAmmo* ammo, const FHitResult& hitResult);
};
