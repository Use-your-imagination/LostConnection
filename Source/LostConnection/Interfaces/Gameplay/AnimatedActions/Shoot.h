// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Shoot.generated.h"

UINTERFACE(BlueprintType)
class UShoot : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IShoot
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void shoot() = 0;

	UFUNCTION()
	virtual void resetShoot() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void onShoot();

public:
	IShoot() = default;
};
