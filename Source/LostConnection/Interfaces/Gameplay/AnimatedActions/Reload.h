// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Reload.generated.h"

UINTERFACE(BlueprintType)
class UReload : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTCONNECTION_API IReload
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void reloadVisual() = 0;

	UFUNCTION(BlueprintImplementableEvent)
	void reloadEventVisual();

	UFUNCTION()
	virtual void reloadLogic() = 0;

	UFUNCTION(BlueprintImplementableEvent)
	void reloadEventLogic();

public:
	IReload() = default;

	UFUNCTION()
	virtual void reload();
};
