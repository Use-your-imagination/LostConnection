// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/Actor.h"

#include "OperatorsLibrary.generated.h"

UENUM(BlueprintType)
enum class EThreeWayComparisonOperator : uint8
{
	less UMETA(DisplayName = Less),
	equal UMETA(DisplayName = Equal),
	greater UMETA(DisplayName = Greater)
};

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(int32, FObjectsThreeWayComparison, const UObject*, left, const UObject*, right);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(int32, FActorsThreeWayComparison, const AActor*, left, const AActor*, right);

UCLASS()
class BLUEPRINTSALGORITHMS_API UOperatorsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	* Compare Integers 
	*/
	UFUNCTION(Category = "Utility|Operators", BlueprintCallable, Meta = (DisplayName = "Integer <=> Integer", CompactNodeTitle = "<=>", ExpandEnumAsExecs = "out"))
	static void intToInt(int32 left, int32 right, EThreeWayComparisonOperator& out);

	/** 
	* Compare Integer with Integer64 
	*/
	UFUNCTION(Category = "Utility|Operators", BlueprintCallable, Meta = (DisplayName = "Integer <=> Integer64", CompactNodeTitle = "<=>", ExpandEnumAsExecs = "out"))
	static void intToInt64(int32 left, int64 right, EThreeWayComparisonOperator& out);

	/** 
	* Compare Integer with Float 
	*/
	UFUNCTION(Category = "Utility|Operators", BlueprintCallable, Meta = (DisplayName = "Integer <=> Float", CompactNodeTitle = "<=>", ExpandEnumAsExecs = "out"))
	static void intToFloat(int32 left, float right, EThreeWayComparisonOperator& out);

	/** 
	* Compare Integers64 
	*/
	UFUNCTION(Category = "Utility|Operators", BlueprintCallable, Meta = (DisplayName = "Integer64 <=> Integer64", CompactNodeTitle = "<=>", ExpandEnumAsExecs = "out"))
	static void int64ToInt64(int64 left, int64 right, EThreeWayComparisonOperator& out);

	/** 
	* Compare Integer64 with Float 
	*/
	UFUNCTION(Category = "Utility|Operators", BlueprintCallable, Meta = (DisplayName = "Integer64 <=> Float", CompactNodeTitle = "<=>", ExpandEnumAsExecs = "out"))
	static void int64ToFloat(int64 left, float right, EThreeWayComparisonOperator& out);

	/** 
	* Compare Floats 
	*/
	UFUNCTION(Category = "Utility|Operators", BlueprintCallable, Meta = (DisplayName = "Float <=> Float", CompactNodeTitle = "<=>", ExpandEnumAsExecs = "out"))
	static void floatToFloat(float left, float right, EThreeWayComparisonOperator& out);

	/**
	* Compare Objects
	* Predicate returns -1 if left < right
	* Predicate returns 0 if left == right
	* Predicate returns 1 if left > right
	*/
	UFUNCTION(Category = "Utility|Operators", BlueprintCallable, Meta = (DisplayName = "Object <=> Object", CompactNodeTitle = "<=>", ExpandEnumAsExecs = "out"))
	static void objectToObject(const UObject* left, const UObject* right, const FObjectsThreeWayComparison& predicate, EThreeWayComparisonOperator& out);

	/**
	* Compare Actors
	* Predicate returns -1 if left < right
	* Predicate returns 0 if left == right
	* Predicate returns 1 if left > right
	*/
	UFUNCTION(Category = "Utility|Operators", BlueprintCallable, Meta = (DisplayName = "Object <=> Object", CompactNodeTitle = "<=>", ExpandEnumAsExecs = "out"))
	static void actorToActor(const AActor* left, const AActor* right, const FActorsThreeWayComparison& predicate, EThreeWayComparisonOperator& out);
};
