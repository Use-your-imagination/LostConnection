// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/Actor.h"

#include "SortingLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FIntegerSortPredicate, int32, first, int32, second);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FInteger64SortPredicate, int64, first, int64, second);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FFloatSortPredicate, float, first, float, second);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FStringSortPredicate, const FString&, first, const FString&, second);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FNameSortPredicate, const FName&, first, const FName&, second);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FTextSortPredicate, const FText&, first, const FText&, second);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FObjectSortPredicate, const UObject*, first, const UObject*, second);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FActorSortPredicate, const AActor*, first, const AActor*, second);

/**
* Provides types of sorting
*/
UENUM(BlueprintType)
enum class ESortingType : uint8
{
	byPredicate UMETA(DisplayName = "By Predicate"),
	standard UMETA(DisplayName = "Standard Way")
};

UCLASS()
class BLUEPRINTSALGORITHMS_API USortingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Sort Array of Integers with custom predicate(if lower returns true)
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (AutoCreateRefTerm = "predicate", CompactNodeTitle = "Sort By Reference"))
	static UPARAM(DisplayName = SortedArray) TArray<int32>& sortByReferenceIntegerArray(UPARAM(ref) TArray<int32>& arrayReference, const FIntegerSortPredicate& predicate, ESortingType& type);

	/**
	* Sort Array of Integers64 with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (AutoCreateRefTerm = "predicate", CompactNodeTitle = "Sort By Reference"))
	static UPARAM(DisplayName = SortedArray) TArray<int64>& sortByReferenceInteger64Array(UPARAM(ref) TArray<int64>& arrayReference, const FInteger64SortPredicate& predicate, ESortingType& type);

	/** 
	* Sort Array of Floats with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (AutoCreateRefTerm = "predicate", CompactNodeTitle = "Sort By Reference"))
	static UPARAM(DisplayName = SortedArray) TArray<float>& sortByReferenceFloatArray(UPARAM(ref) TArray<float>& arrayReference, const FFloatSortPredicate& predicate, ESortingType& type);

	/**
	* Sort Array of Strings with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (AutoCreateRefTerm = "predicate", CompactNodeTitle = "Sort By Reference"))
	static UPARAM(DisplayName = SortedArray) TArray<FString>& sortByReferenceStringArray(UPARAM(ref) TArray<FString>& arrayReference, const FStringSortPredicate& predicate, ESortingType& type);

	/**
	* Sort Array of Names with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (CompactNodeTitle = "Sort By Reference"))
	static UPARAM(DisplayName = SortedArray) TArray<FName>& sortByReferenceNameArray(UPARAM(ref) TArray<FName>& arrayReference, const FNameSortPredicate& predicate);

	/**
	* Sort Array of Texts with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (CompactNodeTitle = "Sort By Reference"))
	static UPARAM(DisplayName = SortedArray) TArray<FText>& sortByReferenceTextArray(UPARAM(ref) TArray<FText>& arrayReference, const FTextSortPredicate& predicate);

	/** 
	* Sort Array of custom Objects with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (CompactNodeTitle = "Sort By Reference"))
	static UPARAM(DisplayName = SortedArray) TArray<UObject*>& sortByReferenceObjectArray(UPARAM(ref) TArray<UObject*>& arrayReference, const FObjectSortPredicate& predicate);

	/**
	* Sort Array of custom Actors with custom predicate(if lower returns true)
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (CompactNodeTitle = "Sort By Reference"))
	static UPARAM(DisplayName = SortedArray) TArray<AActor*>& sortByReferenceActorArray(UPARAM(ref) TArray<AActor*>& arrayReference, const FActorSortPredicate& predicate);

	/** 
	* Sort Array of Integers with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (AutoCreateRefTerm = "predicate", CompactNodeTitle = "Sort"))
	static UPARAM(DisplayName = SortedArray) TArray<int32> sortIntegerArray(const TArray<int32>& array, const FIntegerSortPredicate& predicate, ESortingType& type);

	/**
	* Sort Array of Integers64 with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (AutoCreateRefTerm = "predicate", CompactNodeTitle = "Sort"))
	static UPARAM(DisplayName = SortedArray) TArray<int64> sortInteger64Array(const TArray<int64>& array, const FInteger64SortPredicate& predicate, ESortingType& type);

	/** 
	* Sort Array of Floats with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (AutoCreateRefTerm = "predicate", CompactNodeTitle = "Sort"))
	static UPARAM(DisplayName = SortedArray) TArray<float> sortFloatArray(const TArray<float>& array, const FFloatSortPredicate& predicate, ESortingType& type);

	/** 
	* Sort Array of Strings with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (AutoCreateRefTerm = "predicate", CompactNodeTitle = "Sort"))
	static UPARAM(DisplayName = SortedArray) TArray<FString> sortStringArray(const TArray<FString>& array, const FStringSortPredicate& predicate, ESortingType& type);

	/** 
	* Sort Array of Names with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (CompactNodeTitle = "Sort"))
	static UPARAM(DisplayName = SortedArray) TArray<FName> sortNameArray(const TArray<FName>& array, const FNameSortPredicate& predicate);

	/** 
	* Sort Array of Texts with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (CompactNodeTitle = "Sort"))
	static UPARAM(DisplayName = SortedArray) TArray<FText> sortTextArray(const TArray<FText>& array, const FTextSortPredicate& predicate);

	/** 
	* Sort Array of custom Objects with custom predicate(if lower returns true) 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (CompactNodeTitle = "Sort"))
	static UPARAM(DisplayName = SortedArray) TArray<UObject*> sortObjectArray(const TArray<UObject*>& array, const FObjectSortPredicate& predicate);

	/**
	* Sort Array of custom Actors with custom predicate(if lower returns true)
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, Meta = (CompactNodeTitle = "Sort"))
	static UPARAM(DisplayName = SortedArray) TArray<AActor*> sortActorArray(const TArray<AActor*>& array, const FActorSortPredicate& predicate);

	/** 
	* Check is Array sorted by custom predicate or if predicate is empty by '<' operator 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "IsSorted", AutoCreateRefTerm = "predicate"))
	static UPARAM(DisplayName = IsSorted) bool isSortedIntegerArray(const TArray<int32>& array, const FIntegerSortPredicate& predicate, ESortingType& type);

	/** 
	* Check is Array sorted by custom predicate or if predicate is empty by '<' operator 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "IsSorted", AutoCreateRefTerm = "predicate"))
	static UPARAM(DisplayName = IsSorted) bool isSortedInteger64Array(const TArray<int64>& array, const FInteger64SortPredicate& predicate, ESortingType& type);

	/** 
	* Check is Array sorted by custom predicate or if predicate is empty by '<' operator 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "IsSorted", AutoCreateRefTerm = "predicate"))
	static UPARAM(DisplayName = IsSorted) bool isSortedFloatArray(const TArray<float>& array, const FFloatSortPredicate& predicate, ESortingType& type);

	/** 
	* Check is Array sorted by custom predicate or if predicate is empty by '<' operator 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "IsSorted", AutoCreateRefTerm = "predicate"))
	static UPARAM(DisplayName = IsSorted) bool isSortedStringArray(const TArray<FString>& array, const FStringSortPredicate& predicate, ESortingType& type);

	/** 
	* Check is Array sorted by custom predicate 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "IsSorted"))
	static UPARAM(DisplayName = IsSorted) bool isSortedNameArray(const TArray<FName>& array, const FNameSortPredicate& predicate);

	/** 
	* Check is Array sorted by custom predicate 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "IsSorted"))
	static UPARAM(DisplayName = IsSorted) bool isSortedTextArray(const TArray<FText>& array, const FTextSortPredicate& predicate);

	/** 
	* Check is Array sorted by custom predicate 
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "IsSorted"))
	static UPARAM(DisplayName = IsSorted) bool isSortedObjectArray(const TArray<UObject*>& array, const FObjectSortPredicate& predicate);

	/**
	* Check is Array sorted by custom predicate
	*/
	UFUNCTION(Category = "Utility|Sorting", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "IsSorted"))
	static UPARAM(DisplayName = IsSorted) bool isSortedActorArray(const TArray<AActor*>& array, const FActorSortPredicate& predicate);
};
