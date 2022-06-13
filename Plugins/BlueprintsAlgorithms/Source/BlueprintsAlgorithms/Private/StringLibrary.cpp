// Copyright (c) 2022 Arkadiy Zakharov

#include "StringLibrary.h"

FString& UStringLibrary::toUpperCaseReference(FString& sourceString, int32 characterIndex)
{
	TCHAR& symbol = sourceString[characterIndex];

	symbol = FChar::ToUpper(symbol);

	return sourceString;
}

FString UStringLibrary::toUpperCase(const FString& sourceString, int32 characterIndex)
{
	FString result = sourceString;

	UStringLibrary::toUpperCaseReference(result, characterIndex);

	return result;
}

FString& UStringLibrary::toLowerCaseReference(FString& sourceString, int32 characterIndex)
{
	TCHAR& symbol = sourceString[characterIndex];

	symbol = FChar::ToUpper(symbol);

	return sourceString;
}

FString UStringLibrary::toLowerCase(const FString& sourceString, int32 characterIndex)
{
	FString result = sourceString;

	UStringLibrary::toLowerCaseReference(result, characterIndex);

	return result;
}
