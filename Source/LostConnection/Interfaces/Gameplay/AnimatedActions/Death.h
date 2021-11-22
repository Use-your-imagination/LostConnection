// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Death.generated.h"

UINTERFACE(BlueprintType)
class UDeath : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTCONNECTION_API IDeath
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void deathVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void deathEventVisual();

	UFUNCTION()
	virtual void deathLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void deathEventLogic();

public:
	IDeath() = default;

	UFUNCTION()
	virtual void death();
};
