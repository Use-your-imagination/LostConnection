// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ScriptInterface.h"
#include "GameFramework/InputSettings.h"

#include "Engine/LoadingScreenInfo.h"
#include "UI/InventoryWidget.h"
#include "UI/VideoSettingsWidget.h"
#include "Utility/UtilityStructures.h"

#include "UtilityBlueprintFunctionLibrary.generated.h"

UCLASS()
class LOSTCONNECTION_API UUtilityBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Category = "Utility|Strings", BlueprintCallable, BlueprintPure)
	static FString firstSymbolToUpperCase(const FString& string);

	UFUNCTION(Category = "Utility|Hotkeys", BlueprintCallable)
	static void rebindHotkeys(const TMap<FName, FString>& newHotkeys);

	UFUNCTION(Category = "Utility|Animations", BlueprintCallable)
	static void cancelCurrentAbilityAnimation(const TScriptInterface<class ICaster>& caster);

	UFUNCTION(Category = "Utility|Animations", BlueprintCallable, BlueprintPure)
	static bool isAnyAnimationActive(const TScriptInterface<class ICaster>& caster);

	UFUNCTION(Category = "Utility|AllOf", BlueprintCallable, BlueprintPure)
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

	/**
	* Create actor with loading screen
	* @param endCondition Condition for calling onEndLoadCallback and destroying this actor
	* @param loadingScreenClass User widget for loading screen
	* @param deleteLoadingScreenWidget Remove loading screen with actor destroying
	*/
	UFUNCTION(Category = "Utility|LoadingScreen", BlueprintCallable, Meta = (AutoCreateRefTerm = "onBeginLoadCallback, onEndLoadCallback, endCondition"))
	static ALoadingScreenInfo* createLoadingScreenInfo
	(
		class ALostConnectionGameState* gameState,
		const FCallbackDelegate& onBeginLoadCallback,
		const FCallbackDelegate& onEndLoadCallback,
		const FEndConditionDelegate& endCondition,
		TSubclassOf<UUserWidget> loadingScreenClass,
		bool deleteLoadingScreenWidget = true
	);

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

	UFUNCTION(Category = "Utility|Levels", BlueprintCallable, BlueprintPure)
	static FString getRoomName(const TSoftObjectPtr<UWorld>& room);

	UFUNCTION(Category = "Utility|VideoSettings", BlueprintCallable)
	static void applyVideoSettings(const FVideoSettings& settings);

	UFUNCTION(Category = "Utility|VideoSettings", BlueprintCallable)
	static void addVideoSetting(UPARAM(ref) FVideoSettings& settings, UVideoSettingsWidget* widget, const FApplySettingsDelegate& delegate);

	UFUNCTION(Category = "Utility|World", BlueprintCallable, BlueprintPure, Meta = (DefaultToSelf = "actor"))
	static class ALostConnectionGameState* getLostConnectionGameState(AActor* actor);

	UFUNCTION(Category = "Utility|World", BlueprintCallable, BlueprintPure, Meta = (DefaultToSelf = "pawn"))
	static class ALostConnectionPlayerState* getLostConnectionPlayerState(APawn* pawn);

	UFUNCTION(Category = "Utility|Delegates", BlueprintCallable)
	static void setStandardDelegate(UPARAM(ref) FStandardDelegateHolder& holder, const FStandardDelegate& delegate);

	UFUNCTION(Category = "Utility|Delegates", BlueprintCallable)
	static bool callStandardDelegate(const FStandardDelegateHolder& holder);
};
