#include "UtilityBlueprintFunctionLibrary.h"

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
