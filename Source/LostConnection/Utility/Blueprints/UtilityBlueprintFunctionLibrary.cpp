#include "UtilityBlueprintFunctionLibrary.h"

#include <algorithm>

#include "GameFramework/InputSettings.h"

#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Characters/BaseDrone.h"
#include "Characters/BaseBotCaster.h"
#include "Utility/MultiplayerUtility.h"

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

			if (key->Find(TEXT(" Ctrl")) != INDEX_NONE)
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

void UUtilityBlueprintFunctionLibrary::cancelCurrentAbilityAnimation(TScriptInterface<ICaster> caster)
{
	MultiplayerUtility::runOnServerReliableWithMulticast(caster.GetObject(), "cancelCurrentAbilityAnimation");
}

bool UUtilityBlueprintFunctionLibrary::isAnyAnimationActive(TScriptInterface<ICaster> caster)
{
	if (!caster.GetObject())
	{
		return false;
	}

	UAnimInstance* animInstance = Cast<ABaseCharacter>(caster.GetObject())->GetMesh()->GetAnimInstance();
	const TArray<UAnimMontage*>& animations = caster->getAbilitiesAnimations();
	
	return std::any_of(animations.begin(), animations.end(), [&animInstance](const UAnimMontage* montage) { return animInstance->Montage_IsPlaying(montage); });
}
