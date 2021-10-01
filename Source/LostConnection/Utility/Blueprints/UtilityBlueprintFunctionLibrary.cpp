#include "UtilityBlueprintFunctionLibrary.h"

#include "GameFramework/InputSettings.h"

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
