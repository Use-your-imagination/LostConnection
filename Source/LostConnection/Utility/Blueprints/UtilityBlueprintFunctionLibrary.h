// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ScriptInterface.h"
#include "GameFramework/InputSettings.h"

#include "Engine/LoadingScreenInfo.h"
#include "UI/InventoryWidget.h"

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

	/**
	* Set scalar parameter for each material in mesh
	*/
	UFUNCTION(Category = "Utility|Materials", BlueprintCallable, Meta = (DisplayName = "Set material scalar parameter", CompactNodeTitle = "Material Scalar"))
	static void setMaterialScalarParameter(USkeletalMeshComponent* mesh, FName parameterName, float value);

	/**
	* Set linear parameter for each material in mesh
	*/
	UFUNCTION(Category = "Utility|Materials", BlueprintCallable, Meta = (DisplayName = "Set material linear color parameter", CompactNodeTitle = "Material Linear Color"))
	static void setMaterialLinearColorParameter(USkeletalMeshComponent* mesh, FName parameterName, FLinearColor value);

	UFUNCTION(Category = "Utility|AssetManager", BlueprintCallable, BlueprintPure)
	static class ULostConnectionAssetManager* getAssetManager();

	UFUNCTION(Category = "Utility|LoadingScreen", BlueprintCallable, Meta = (AutoCreateRefTerm = "onBeginLoadCallback, onEndLoadCallback"))
	static ALoadingScreenInfo* createLoadingScreenInfo(class ALostConnectionGameState* gameState, const FCallbackDelegate& onBeginLoadCallback, const FCallbackDelegate& onEndLoadCallback);

	UFUNCTION(Category = "Utility|Spawning", BlueprintCallable, Meta = (HidePin = worldContext, DefaultToSelf = worldContext))
	static class ABaseDrone* spawnDrone(TSubclassOf<class ABaseDrone> droneClass, const FTransform& transform, APlayerController* controller, UObject* worldContext);

	UFUNCTION(Category = "Utility|Hotkeys", BlueprintCallable, BlueprintPure)
	static TArray<FInputActionKeyMapping> getActionMapping(FName actionName);

	UFUNCTION(Category = "Utility|UI", BlueprintCallable)
	static void showMouseCursor(APlayerController* playerController, bool isShowMouseCursor);

	UFUNCTION(Category = "Utility|UI", BlueprintCallable, BlueprintPure)
	static FText getWeaponsDropChance(int32 lootPoints, const TArray<class UBaseWeaponsLootFunction*>& weaponsLootFunctions);

	UFUNCTION(Category = "Utility|UI", BlueprintCallable, BlueprintPure)
	static FText getModulesDropChance(int32 lootPoints, const TArray<class UBaseModulesLootFunction*>& modulesLootFunctions);

	UFUNCTION(Category = "Utility|UI", BlueprintCallable, BlueprintPure)
	static FText getWeaponModulesDropChance(int32 lootPoints, const TArray<class UBaseWeaponModulesLootFunction*>& weaponModulesLootFunctions);

	UFUNCTION(Category = "Loot|Ammo", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Get Current Position"))
	static FTransform getAmmoDropableCurrentPosition(TScriptInterface<class IAmmoDropable> ammoDropable);
};
