// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "PlatinumModule.generated.h"

UINTERFACE(BlueprintType)
class UPlatinumModule : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IPlatinumModule
{
	GENERATED_BODY()

public:
	IPlatinumModule() = default;

	virtual void uniqueAction(TObjectPtr<AActor> caller) = 0;
};
