#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ScriptInterface.h"

#include "UtilityBlueprintFunctionLibrary.generated.h"

UCLASS()
class LOSTCONNECTION_API UUtilityBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Category = Utility, BlueprintCallable, BlueprintPure)
	static FString firstSymbolToUpperCase(const FString& string);

	UFUNCTION(Category = Utility, BlueprintCallable)
	static void rebindHotkeys(const TMap<FName, FString>& newHotkeys);

	UFUNCTION(Category = Utility, BlueprintCallable)
	static void cancelCurrentAbilityAnimation(TScriptInterface<class ICaster> caster);
};
