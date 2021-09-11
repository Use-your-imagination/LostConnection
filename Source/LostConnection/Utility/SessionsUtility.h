#pragma once

#include "CoreMinimal.h"

#include "Online.h"
#include "Net/UnrealNetwork.h"
#include "FindSessionsCallbackProxy.h"

#include "SessionsUtility.generated.h"

UENUM(BlueprintType)
enum executionOutputs
{
	Success UMETA(DisplayName = "Success"),
	Fail UMETA(DisplayName = "Fail")
};

UCLASS(MinimalApi)
class USessionsUtility : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session", Meta = (ExpandEnumAsExecs = "branches"))
	static void getSessionName(const FBlueprintSessionResult& sessionResult, FString& sessionName, TEnumAsByte<executionOutputs>& branches);
};
