// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "LogicLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FBooleanPredicate, bool, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FIntegerPredicate, int32, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FInteger64Predicate, int64, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FFloatPredicate, float, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FStringPredicate, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FNamePredicate, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FTextPredicate, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FVectorPredicate, const FVector&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FVector2DPredicate, const FVector2D&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FColorPredicate, const FColor&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FLinearColorPredicate, const FLinearColor&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FObjectPredicate, const UObject*, object);

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FActorPredicate, const AActor*, actor);

UCLASS()
class BLUEPRINTSALGORITHMS_API ULogicLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
#pragma region AllOf
	/** 
	* Returns true if all values returns true in predicate, if no predicate passed returns true if all values returns true 
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (AutoCreateRefTerm = "predicate", DisplayName = "All Of Boolean Array", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfBooleanArray(const TArray<bool>& values, const FBooleanPredicate& predicate);

	/**
	* Returns true if all values returns true in predicate 
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Integer Array", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfIntegerArray(const TArray<int32>& values, const FIntegerPredicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Integer Set", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfIntegerSet(const TSet<int32>& values, const FIntegerPredicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Integer64 Array", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfInteger64Array(const TArray<int64>& values, const FInteger64Predicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Integer64 Set", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfInteger64Set(const TSet<int64>& values, const FInteger64Predicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Float Array", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfFloatArray(const TArray<float>& values, const FFloatPredicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Float Set", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfFloatSet(const TSet<float>& values, const FFloatPredicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of String Array", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfStringArray(const TArray<FString>& values, const FStringPredicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of String Set", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfStringSet(const TSet<FString>& values, const FStringPredicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Name Array", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfNameArray(const TArray<FName>& values, const FNamePredicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Name Set", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfNameSet(const TSet<FName>& values, const FNamePredicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Text Array", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfTextArray(const TArray<FText>& values, const FTextPredicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Object Array", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfObjectArray(const TArray<UObject*>& values, const FObjectPredicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Object Set", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfObjectSet(const TSet<UObject*>& values, const FObjectPredicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Actor Array", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfActorArray(const TArray<AActor*>& values, const FActorPredicate& predicate);

	/**
	* Returns true if all values returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "All Of Actor Set", CompactNodeTitle = "AllOf"))
	static UPARAM(DisplayName = Result) bool allOfActorSet(const TSet<AActor*>& values, const FActorPredicate& predicate);
#pragma endregion

#pragma region AnyOf
	/** 
	* Returns true if any value returns true in predicate, if no predicate passed returns true if any value returns true 
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (AutoCreateRefTerm = "predicate", DisplayName = "Any of Boolean Array", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfBooleanArray(const TArray<bool>& values, const FBooleanPredicate& predicate);

	/**
	* Returns true if any value returns true in predicate 
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Integer Array", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfIntegerArray(const TArray<int32>& values, const FIntegerPredicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Integer Set", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfIntegerSet(const TSet<int32>& values, const FIntegerPredicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Integer64 Array", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfInteger64Array(const TArray<int64>& values, const FInteger64Predicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Integer64 Set", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfInteger64Set(const TSet<int64>& values, const FInteger64Predicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Float Array", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfFloatArray(const TArray<float>& values, const FFloatPredicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Float Set", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfFloatSet(const TSet<float>& values, const FFloatPredicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of String Array", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfStringArray(const TArray<FString>& values, const FStringPredicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of String Set", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfStringSet(const TSet<FString>& values, const FStringPredicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Name Array", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfNameArray(const TArray<FName>& values, const FNamePredicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Name Set", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfNameSet(const TSet<FName>& values, const FNamePredicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Text Array", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfTextArray(const TArray<FText>& values, const FTextPredicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Object Array", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfObjectArray(const TArray<UObject*>& values, const FObjectPredicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Object Set", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfObjectSet(const TSet<UObject*>& values, const FObjectPredicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Actor Array", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfActorArray(const TArray<AActor*>& values, const FActorPredicate& predicate);

	/**
	* Returns true if any value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Logic", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Any Of Actor Set", CompactNodeTitle = "AnyOf"))
	static UPARAM(DisplayName = Result) bool anyOfActorSet(const TSet<AActor*>& values, const FActorPredicate& predicate);
#pragma endregion
};
