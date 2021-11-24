// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Constants.generated.h"

UCLASS()
class LOSTCONNECTION_API UConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static const FString projectVersion;
	
public:
	UFUNCTION(Category = Constants, BlueprintCallable, BlueprintPure)
	static FText getProjectVersion();
};
