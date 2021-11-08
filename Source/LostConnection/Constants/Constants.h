#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Constants.generated.h"

UCLASS()
class LOSTCONNECTION_API UConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Category = Constants, BlueprintCallable, BlueprintPure)
	static FText getProjectVersion();
};
