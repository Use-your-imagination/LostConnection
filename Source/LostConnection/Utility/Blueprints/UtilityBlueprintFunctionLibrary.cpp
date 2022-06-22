// Copyright (c) 2021 Use Your Imagination

#include "UtilityBlueprintFunctionLibrary.h"

#include "Algo/AnyOf.h"
#include "Algo/AllOf.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/Pawn.h"
#include "Components/Button.h"

#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Characters/BaseDrone.h"
#include "Characters/BaseBotCaster.h"
#include "Utility/MultiplayerUtility.h"
#include "Engine/LostConnectionGameState.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "Interfaces/Loot/AmmoDropable.h"

FString appendLootDropChance(int32 lootPoints, const UBaseLootFunction* lootFunction)
{
	float chance = lootFunction->calculateLootChance(lootPoints);
	const FString& lootName = lootFunction->getLootName().ToString();

	return chance == 0.0f ?
		FString::Printf(TEXT("%s: 0%%"), *lootName) :
		chance < 1.0f ?
		FString::Printf(TEXT("%s: < 1%%"), *lootName) :
		FString::Printf(TEXT("%s: %.0f%%"), *lootName, chance);
}

FString UUtilityBlueprintFunctionLibrary::firstSymbolToUpperCase(const FString& string)
{
	if (!string.Len())
	{
		return string;
	}

	FString result = string;

	if (result[0] >= 'a' && result[0] <= 'z')
	{
		result[0] -= 32;
	}

	return result;
}

void UUtilityBlueprintFunctionLibrary::rebindHotkeys(const TMap<FName, FString>& newHotkeys)
{
	UInputSettings* settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	static const TMap<FString, FString> numbers =
	{
		{ "0", "Zero" },
		{ "1", "One" },
		{ "2", "Two" },
		{ "3", "Three" },
		{ "4", "Four" },
		{ "5", "Five" },
		{ "6", "Six" },
		{ "7", "Seven" },
		{ "8", "Eight" },
		{ "9", "Nine" }
	};

	if (!settings)
	{
		return;
	}

	TArray<FInputActionKeyMapping>& hotkeys = const_cast<TArray<FInputActionKeyMapping>&>(settings->GetActionMappings());

	for (auto& hotkey : hotkeys)
	{
		const FString* key = newHotkeys.Find(hotkey.ActionName);

		if (key)
		{
			int32 index = 0;

			if (key->Find(" Ctrl") != INDEX_NONE)
			{
				hotkey.Key = FKey(FName(key->Replace(TEXT(" Ctrl"), TEXT("Control"))));
			}
			else if (key->FindChar(' ', index))
			{
				hotkey.Key = FKey(FName(key->Replace(TEXT(" "), TEXT(""))));
			}
			else if (numbers.Find(*key))
			{
				hotkey.Key = FKey(FName(numbers[*key]));
			}
			else
			{
				hotkey.Key = FKey(FName(*key));
			}
		}
	}

	settings->SaveKeyMappings();

	for (TObjectIterator<UPlayerInput> it; it; ++it)
	{
		it->ForceRebuildingKeyMaps(true);
	}
}

void UUtilityBlueprintFunctionLibrary::cancelCurrentAbilityAnimation(const TScriptInterface<ICaster>& caster)
{
	MultiplayerUtility::runOnServerReliableWithMulticast(Cast<APawn>(caster.GetObject()), "cancelCurrentAbilityAnimation");
}

bool UUtilityBlueprintFunctionLibrary::isAnyAnimationActive(const TScriptInterface<ICaster>& caster)
{
	if (!caster.GetObject())
	{
		return false;
	}

	UAnimInstance* animInstance = Cast<ABaseCharacter>(caster.GetObject())->GetMesh()->GetAnimInstance();
	const TArray<UAnimMontage*>& animations = caster->getAbilitiesAnimations();

	return Algo::AnyOf(animations, [&animInstance](const UAnimMontage* montage) { return animInstance->Montage_IsPlaying(montage); });
}

bool UUtilityBlueprintFunctionLibrary::allOfFloat(const TArray<float>& values, float compareValue)
{
	return Algo::AllOf(values, [&compareValue](float value) { return value == compareValue; });
}

void UUtilityBlueprintFunctionLibrary::setMaterialScalarParameter(USkeletalMeshComponent* mesh, FName parameterName, float value)
{
	TArray<UMaterialInterface*> materials = mesh->GetMaterials();

	for (UMaterialInterface* material : materials)
	{
		Cast<UMaterialInstanceDynamic>(material)->SetScalarParameterValue(parameterName, value);
	}
}

void UUtilityBlueprintFunctionLibrary::setMaterialLinearColorParameter(USkeletalMeshComponent* mesh, FName parameterName, FLinearColor value)
{
	TArray<UMaterialInterface*> materials = mesh->GetMaterials();

	for (UMaterialInterface* material : materials)
	{
		Cast<UMaterialInstanceDynamic>(material)->SetVectorParameterValue(parameterName, value);
	}
}

ULostConnectionAssetManager* UUtilityBlueprintFunctionLibrary::getAssetManager()
{
	return &StaticCast<ULostConnectionAssetManager&>(UAssetManager::Get());
}

ALoadingScreenInfo* UUtilityBlueprintFunctionLibrary::createLoadingScreenInfo(ALostConnectionGameState* gameState, const FCallbackDelegate& onBeginLoadCallback, const FCallbackDelegate& onEndLoadCallback)
{
	ALoadingScreenInfo* info = gameState->spawn<ALoadingScreenInfo>({});

	info->setOnBeginLoadCallback(onBeginLoadCallback);

	info->setOnEndLoadCallback(onEndLoadCallback);

	info->FinishSpawning({}, true);

	return info;
}

ABaseDrone* UUtilityBlueprintFunctionLibrary::spawnDrone(TSubclassOf<ABaseDrone> droneClass, const FTransform& transform, APlayerController* controller, UObject* worldContext)
{
	UWorld* world = GEngine->GetWorldFromContextObject(worldContext, EGetWorldErrorMode::ReturnNull);

	if (world)
	{
		ABaseDrone* drone = world->SpawnActorDeferred<ABaseDrone>(droneClass, {});

		controller->Possess(drone);

		drone->FinishSpawning(transform);

		return drone;
	}

	return nullptr;
}

TArray<FInputActionKeyMapping> UUtilityBlueprintFunctionLibrary::getActionMapping(FName actionName)
{
	TArray<FInputActionKeyMapping> result;
	GetDefault<UInputSettings>()->GetActionMappingByName(actionName, result);

	return result;
}

void UUtilityBlueprintFunctionLibrary::showMouseCursor(APlayerController* playerController, bool isShowMouseCursor)
{
	playerController->bShowMouseCursor = isShowMouseCursor;

	playerController->bEnableClickEvents = isShowMouseCursor;

	playerController->bEnableMouseOverEvents = isShowMouseCursor;
}

FText UUtilityBlueprintFunctionLibrary::getWeaponsDropChance(int32 lootPoints, const TArray<UBaseWeaponsLootFunction*>& weaponsLootFunctions)
{
	FString result;

	for (const auto& lootFunction : weaponsLootFunctions)
	{
		if (result.Len())
		{
			result += '\n';
		}

		result += appendLootDropChance(lootPoints, lootFunction);
	}

	return FText::FromString(result);
}

FText UUtilityBlueprintFunctionLibrary::getModulesDropChance(int32 lootPoints, const TArray<UBaseModulesLootFunction*>& modulesLootFunctions)
{
	FString result;

	for (const auto& lootFunction : modulesLootFunctions)
	{
		if (result.Len())
		{
			result += '\n';
		}

		result += appendLootDropChance(lootPoints, lootFunction);
	}

	return FText::FromString(result);
}

FText UUtilityBlueprintFunctionLibrary::getWeaponModulesDropChance(int32 lootPoints, const TArray<UBaseWeaponModulesLootFunction*>& weaponModulesLootFunctions)
{
	FString result;

	for (const auto& lootFunction : weaponModulesLootFunctions)
	{
		if (result.Len())
		{
			result += '\n';
		}

		result += appendLootDropChance(lootPoints, lootFunction);
	}

	return FText::FromString(result);
}

FTransform UUtilityBlueprintFunctionLibrary::getAmmoDropableCurrentPosition(TScriptInterface<IAmmoDropable> ammoDropable)
{
	return ammoDropable->getCurrentPosition();
}

FString UUtilityBlueprintFunctionLibrary::getRoomName(const TSoftObjectPtr<UWorld>& room)
{
	return room.GetAssetName();
}

void UUtilityBlueprintFunctionLibrary::applyVideoSettings(const FVideoSettings& settings)
{
	TObjectPtr<UGameUserSettings> userSettings = UGameUserSettings::GetGameUserSettings();

	for (const TPair<TObjectPtr<UVideoSettingsWidget>, FApplySettingsDelegate>& applier : settings.settingsAppliers)
	{
		applier.Value.Execute(userSettings, applier.Key->getVideoSettingValue()->GetSelectedIndex());
	}

	userSettings->ApplySettings(false);
}

void UUtilityBlueprintFunctionLibrary::addVideoSetting(FVideoSettings& settings, UVideoSettingsWidget* widget, const FApplySettingsDelegate& delegate)
{
	settings.settingsAppliers.Emplace(widget, delegate);
}
