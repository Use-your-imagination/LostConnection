// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Online.h"
#include "Net/UnrealNetwork.h"
#include "FindSessionsCallbackProxy.h"

#include "Enums.h"

#include "SessionsUtility.generated.h"

UCLASS(MinimalApi)
class USessionsUtility : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session", Meta = (ExpandEnumAsExecs = branches))
	static void getFindedSessionName(const FBlueprintSessionResult& sessionResult, FString& sessionName, EExecutionOutputs& branches);
};
