// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ScriptInterface.h"

#include "Engine/LoadingScreenInfo.h"

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
	static void cancelCurrentAbilityAnimation(const TScriptInterface<class ICaster>& caster);

	UFUNCTION(Category = Utility, BlueprintCallable, BlueprintPure)
	static bool isAnyAnimationActive(const TScriptInterface<class ICaster>& caster);

	UFUNCTION(Category = Utility, BlueprintCallable, BlueprintPure)
	static bool allOfFloat(const TArray<float>& values, float compareValue);

	UFUNCTION(Category = "Utility|AssetManager", BlueprintCallable, BlueprintPure)
	static class ULostConnectionAssetManager* getAssetManager();

	UFUNCTION(Category = "Utility|LoadingScreen", BlueprintCallable, Meta = (AutoCreateRefTerm = "onBeginLoadCallback, onEndLoadCallback"))
	static ALoadingScreenInfo* createLoadingScreenInfo(class ALostConnectionGameState* gameState, const FCallbackDelegate& onBeginLoadCallback, const FCallbackDelegate& onEndLoadCallback);

	UFUNCTION(Category = "Utility|Spawning", BlueprintCallable)
	static class ABaseDrone* spawnDrone(TSubclassOf<class ABaseDrone> droneClass, const FTransform& transform, APlayerController* controller, UObject* worldContext);
};
