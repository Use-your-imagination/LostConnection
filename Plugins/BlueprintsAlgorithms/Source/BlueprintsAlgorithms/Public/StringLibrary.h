// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "StringLibrary.generated.h"

UCLASS()
class BLUEPRINTSALGORITHMS_API UStringLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	* Convert String character to upper case
	*/
	UFUNCTION(Category = "Utility|Strings", BlueprintCallable, Meta = (DisplayName = "To Upper Case", CompactNodeTitle = "ToUpperCase"))
	static UPARAM(DisplayName = ModifiedSourceString) FString& toUpperCaseReference(UPARAM(ref) FString& sourceString, int32 characterIndex);

	/**
	* Convert String character to upper case
	*/
	UFUNCTION(Category = "Utility|Strings", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "To Upper Case", CompactNodeTitle = "ToUpperCase"))
	static UPARAM(DisplayName = NewString) FString toUpperCase(const FString& sourceString, int32 characterIndex);

	/** 
	* Convert String character to lower case
	*/
	UFUNCTION(Category = "Utility|Strings", BlueprintCallable, Meta = (DisplayName = "To Lower Case", CompactNodeTitle = "ToLowerCase"))
	static UPARAM(DisplayName = ModifiedSourceString) FString& toLowerCaseReference(UPARAM(ref) FString& sourceString, int32 characterIndex);

	/** 
	* Convert String character to lower case 
	*/
	UFUNCTION(Category = "Utility|Strings", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "To Lower Case", CompactNodeTitle = "ToLowerCase"))
	static UPARAM(DisplayName = NewString) FString toLowerCase(const FString& sourceString, int32 characterIndex);
};
