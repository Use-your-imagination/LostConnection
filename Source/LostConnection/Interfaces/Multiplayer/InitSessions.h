// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "InitSessions.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UInitSessions : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IInitSessions
{
	GENERATED_BODY()

public:
	IInitSessions() = default;

	UFUNCTION(BlueprintNativeEvent)
	void initSessionList();
};
