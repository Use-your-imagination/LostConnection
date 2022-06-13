// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/Actor.h"

#include "LogicLibrary.h"

#include "UtilityLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FBooleanCallable, UPARAM(ref) bool&, value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FIntegerCallable, UPARAM(ref) int32&, value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FInteger64Callable, UPARAM(ref) int64&, value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FFloatCallable, UPARAM(ref) float&, value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FStringCallable, UPARAM(ref) FString&, value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FNameCallable, UPARAM(ref) FName&, value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FTextCallable, UPARAM(ref) FText&, value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FVectorCallable, UPARAM(ref) FVector&, value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FVector2DCallable, UPARAM(ref) FVector2D&, value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FColorCallable, UPARAM(ref) FColor&, value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FLinearColorCallable, UPARAM(ref) FLinearColor&, value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FObjectCallable, UObject*, object);

DECLARE_DYNAMIC_DELEGATE_OneParam(FActorCallable, AActor*, actor);

#pragma region Mapping
#pragma region Integer
DECLARE_DYNAMIC_DELEGATE_TwoParams(FIntegerBooleanCallback, int32, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FIntegerIntegerCallback, int32, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FIntegerInteger64Callback, int32, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FIntegerFloatCallback, int32, key, float, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FIntegerStringCallback, int32, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FIntegerNameCallback, int32, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FIntegerTextCallback, int32, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FIntegerObjectCallback, int32, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FIntegerActorCallback, int32, key, const AActor*, value);
#pragma endregion
#pragma region Integer64
DECLARE_DYNAMIC_DELEGATE_TwoParams(FInteger64BooleanCallback, int64, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FInteger64IntegerCallback, int64, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FInteger64Integer64Callback, int64, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FInteger64FloatCallback, int64, key, float, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FInteger64StringCallback, int64, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FInteger64NameCallback, int64, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FInteger64TextCallback, int64, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FInteger64ObjectCallback, int64, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FInteger64ActorCallback, int64, key, const AActor*, value);
#pragma endregion
#pragma region Float
DECLARE_DYNAMIC_DELEGATE_TwoParams(FFloatBooleanCallback, float, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FFloatIntegerCallback, float, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FFloatInteger64Callback, float, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FFloatFloatCallback, float, key, float, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FFloatStringCallback, float, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FFloatNameCallback, float, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FFloatTextCallback, float, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FFloatObjectCallback, float, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FFloatActorCallback, float, key, const AActor*, value);
#pragma endregion
#pragma region String
DECLARE_DYNAMIC_DELEGATE_TwoParams(FStringBooleanCallback, const FString&, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FStringIntegerCallback, const FString&, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FStringInteger64Callback, const FString&, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FStringFloatCallback, const FString&, key, float, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FStringStringCallback, const FString&, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FStringNameCallback, const FString&, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FStringTextCallback, const FString&, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FStringObjectCallback, const FString&, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FStringActorCallback, const FString&, key, const AActor*, value);
#pragma endregion
#pragma region Name
DECLARE_DYNAMIC_DELEGATE_TwoParams(FNameBooleanCallback, const FName&, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FNameIntegerCallback, const FName&, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FNameInteger64Callback, const FName&, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FNameFloatCallback, const FName&, key, float, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FNameStringCallback, const FName&, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FNameNameCallback, const FName&, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FNameTextCallback, const FName&, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FNameObjectCallback, const FName&, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FNameActorCallback, const FName&, key, const AActor*, value);
#pragma endregion
#pragma region Object
DECLARE_DYNAMIC_DELEGATE_TwoParams(FObjectBooleanCallback, const UObject*, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FObjectIntegerCallback, const UObject*, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FObjectInteger64Callback, const UObject*, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FObjectFloatCallback, const UObject*, key, float, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FObjectStringCallback, const UObject*, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FObjectNameCallback, const UObject*, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FObjectTextCallback, const UObject*, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FObjectObjectCallback, const UObject*, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FObjectActorCallback, const UObject*, key, const AActor*, value);
#pragma endregion
#pragma region Actor
DECLARE_DYNAMIC_DELEGATE_TwoParams(FActorBooleanCallback, const AActor*, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FActorIntegerCallback, const AActor*, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FActorInteger64Callback, const AActor*, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FActorFloatCallback, const AActor*, key, float, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FActorStringCallback, const AActor*, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FActorNameCallback, const AActor*, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FActorTextCallback, const AActor*, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FActorObjectCallback, const AActor*, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FActorActorCallback, const AActor*, key, const AActor*, value);
#pragma endregion
#pragma endregion

#pragma region MapPredicates
#pragma region Integer
DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FIntegerBooleanPredicate, int32, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FIntegerIntegerPredicate, int32, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FIntegerInteger64Predicate, int32, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FIntegerFloatPredicate, int32, key, float, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FIntegerStringPredicate, int32, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FIntegerNamePredicate, int32, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FIntegerTextPredicate, int32, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FIntegerObjectPredicate, int32, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FIntegerActorPredicate, int32, key, const AActor*, value);
#pragma endregion
#pragma region Integer64
DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FInteger64BooleanPredicate, int64, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FInteger64IntegerPredicate, int64, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FInteger64Integer64Predicate, int64, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FInteger64FloatPredicate, int64, key, float, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FInteger64StringPredicate, int64, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FInteger64NamePredicate, int64, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FInteger64TextPredicate, int64, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FInteger64ObjectPredicate, int64, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FInteger64ActorPredicate, int64, key, const AActor*, value);
#pragma endregion
#pragma region Float
DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FFloatBooleanPredicate, float, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FFloatIntegerPredicate, float, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FFloatInteger64Predicate, float, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FFloatFloatPredicate, float, key, float, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FFloatStringPredicate, float, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FFloatNamePredicate, float, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FFloatTextPredicate, float, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FFloatObjectPredicate, float, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FFloatActorPredicate, float, key, const AActor*, value);
#pragma endregion
#pragma region String
DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FStringBooleanPredicate, const FString&, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FStringIntegerPredicate, const FString&, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FStringInteger64Predicate, const FString&, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FStringFloatPredicate, const FString&, key, float, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FStringStringPredicate, const FString&, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FStringNamePredicate, const FString&, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FStringTextPredicate, const FString&, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FStringObjectPredicate, const FString&, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FStringActorPredicate, const FString&, key, const AActor*, value);
#pragma endregion
#pragma region Name
DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FNameBooleanPredicate, const FName&, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FNameIntegerPredicate, const FName&, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FNameInteger64Predicate, const FName&, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FNameFloatPredicate, const FName&, key, float, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FNameStringPredicate, const FName&, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FNameNamePredicate, const FName&, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FNameTextPredicate, const FName&, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FNameObjectPredicate, const FName&, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FNameActorPredicate, const FName&, key, const AActor*, value);
#pragma endregion
#pragma region Object
DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FObjectBooleanPredicate, const UObject*, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FObjectIntegerPredicate, const UObject*, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FObjectInteger64Predicate, const UObject*, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FObjectFloatPredicate, const UObject*, key, float, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FObjectStringPredicate, const UObject*, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FObjectNamePredicate, const UObject*, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FObjectTextPredicate, const UObject*, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FObjectObjectPredicate, const UObject*, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FObjectActorPredicate, const UObject*, key, const AActor*, value);
#pragma endregion
#pragma region Actor
DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FActorBooleanPredicate, const AActor*, key, bool, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FActorIntegerPredicate, const AActor*, key, int32, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FActorInteger64Predicate, const AActor*, key, int64, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FActorFloatPredicate, const AActor*, key, float, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FActorStringPredicate, const AActor*, key, const FString&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FActorNamePredicate, const AActor*, key, const FName&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FActorTextPredicate, const AActor*, key, const FText&, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FActorObjectPredicate, const AActor*, key, const UObject*, value);

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FActorActorPredicate, const AActor*, key, const AActor*, value);
#pragma endregion
#pragma endregion

UCLASS()
class BLUEPRINTSALGORITHMS_API UUtilityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
#pragma region Spawn
	/**
	* Spawn actor
	* May return null if Already Spawned Actor is not valid or Already Spawned Actor is not spawned yet
	*/
	UFUNCTION(Category = "Utility|Spawn", BlueprintCallable)
	static UPARAM(DisplayName = Actor) AActor* spawnActor
	(
		UPARAM(Meta = (AllowAbstract = "false")) TSubclassOf<AActor> actorClass,
		const FTransform& spawnTransform,
		const AActor* alreadySpawnedActor,
		ESpawnActorCollisionHandlingMethod collision = ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	/**
	* Spawn actor without calling Begin Play
	* You can call other methods
	* When you finish with initialization call Finish Spawn Actor Deferred
	*/
	UFUNCTION(Category = "Utility|Spawn", BlueprintCallable)
	static UPARAM(DisplayName = Actor) AActor* startSpawnActorDeferred
	(
		UPARAM(Meta = (AllowAbstract = "false")) TSubclassOf<AActor> actorClass,
		const AActor* alreadySpawnedActor,
		ESpawnActorCollisionHandlingMethod collision = ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	/**
	* Finish actor spawning
	* Calling Begin Play
	*/
	UFUNCTION(Category = "Utility|Spawn", BlueprintCallable)
	static UPARAM(DisplayName = Actor) AActor* finishSpawnActorDeferred(AActor* notYetSpawnedActor, const FTransform& spawnTransform);
#pragma endregion

#pragma region ForEach
	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each Boolean", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<bool>& forEachBooleanArray(UPARAM(ref) TArray<bool>& array, const FBooleanCallable& callable);

	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each Integer", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<int32>& forEachIntegerArray(UPARAM(ref) TArray<int32>& array, const FIntegerCallable& callable);

	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each Integer64", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<int64>& forEachInteger64Array(UPARAM(ref) TArray<int64>& array, const FInteger64Callable& callable);

	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each Float", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<float>& forEachFloatArray(UPARAM(ref) TArray<float>& array, const FFloatCallable& callable);

	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each String", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<FString>& forEachStringArray(UPARAM(ref) TArray<FString>& array, const FStringCallable& callable);

	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each Name", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<FName>& forEachNameArray(UPARAM(ref) TArray<FName>& array, const FNameCallable& callable);

	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each Text", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<FText>& forEachTextArray(UPARAM(ref) TArray<FText>& array, const FTextCallable& callable);

	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each Vector3", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<FVector>& forEachVectorArray(UPARAM(ref) TArray<FVector>& array, const FVectorCallable& callable);

	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each Vector2", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<FVector2D>& forEachVector2DArray(UPARAM(ref) TArray<FVector2D>& array, const FVector2DCallable& callable);

	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each Color", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<FColor>& forEachColorArray(UPARAM(ref) TArray<FColor>& array, const FColorCallable& callable);

	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each LinearColor", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<FLinearColor>& forEachLinearColorArray(UPARAM(ref) TArray<FLinearColor>& array, const FLinearColorCallable& callable);

	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each Object", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<UObject*>& forEachObjectArray(UPARAM(ref) TArray<UObject*>& array, const FObjectCallable& callable);

	/**
	* Invokes a callable to each element in Array
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each Object", CompactNodeTitle = "ForEach"))
	static UPARAM(DisplayName = Result) TArray<AActor*>& forEachActorArray(UPARAM(ref) TArray<AActor*>& array, const FActorCallable& callable);
#pragma endregion

#pragma region ForEachIf
	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If Boolean", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<bool>& forEachIfBooleanArray(UPARAM(ref) TArray<bool>& array, const FBooleanCallable& callable, const FBooleanPredicate& predicate);

	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If Integer", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<int32>& forEachIfIntegerArray(UPARAM(ref) TArray<int32>& array, const FIntegerCallable& callable, const FIntegerPredicate& predicate);

	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If Integer64", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<int64>& forEachIfInteger64Array(UPARAM(ref) TArray<int64>& array, const FInteger64Callable& callable, const FInteger64Predicate& predicate);

	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If Float", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<float>& forEachIfFloatArray(UPARAM(ref) TArray<float>& array, const FFloatCallable& callable, const FFloatPredicate& predicate);

	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If String", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<FString>& forEachIfStringArray(UPARAM(ref) TArray<FString>& array, const FStringCallable& callable, const FStringPredicate& predicate);

	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If Name", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<FName>& forEachIfNameArray(UPARAM(ref) TArray<FName>& array, const FNameCallable& callable, const FNamePredicate& predicate);

	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If Text", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<FText>& forEachIfTextArray(UPARAM(ref) TArray<FText>& array, const FTextCallable& callable, const FTextPredicate& predicate);

	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If Vector3", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<FVector>& forEachIfVectorArray(UPARAM(ref) TArray<FVector>& array, const FVectorCallable& callable, const FVectorPredicate& predicate);

	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If Vector2", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<FVector2D>& forEachIfVector2DArray(UPARAM(ref) TArray<FVector2D>& array, const FVector2DCallable& callable, const FVector2DPredicate& predicate);

	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If Color", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<FColor>& forEachIfColorArray(UPARAM(ref) TArray<FColor>& array, const FColorCallable& callable, const FColorPredicate& predicate);

	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If LinearColor", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<FLinearColor>& forEachIfLinearColorArray(UPARAM(ref) TArray<FLinearColor>& array, const FLinearColorCallable& callable, const FLinearColorPredicate& predicate);

	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If Object", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<UObject*>& forEachIfObjectArray(UPARAM(ref) TArray<UObject*>& array, const FObjectCallable& callable, const FObjectPredicate& predicate);

	/**
	* Invokes a callable to each element in Array that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|For Each", BlueprintCallable, Meta = (DisplayName = "For Each If Object", CompactNodeTitle = "ForEachIf"))
	static UPARAM(DisplayName = Result) TArray<AActor*>& forEachIfActorArray(UPARAM(ref) TArray<AActor*>& array, const FActorCallable& callable, const FActorPredicate& predicate);
#pragma endregion

#pragma region RemoveIf
	/**
	* Remove element if predicate returns true
	*/
	UFUNCTION(Category = "Utility|Remove If", BlueprintCallable, Meta = (DisplayName = "Remove If Boolean", CompactNodeTitle = "RemoveIf"))
	static UPARAM(DisplayName = ResultArray) TArray<bool>& removeIfBooleanArray(UPARAM(ref) TArray<bool>& array, const FBooleanPredicate& predicate);

	/**
	* Remove element if predicate returns true
	*/
	UFUNCTION(Category = "Utility|Remove If", BlueprintCallable, Meta = (DisplayName = "Remove If Integer", CompactNodeTitle = "RemoveIf"))
	static UPARAM(DisplayName = ResultArray) TArray<int32>& removeIfIntegerArray(UPARAM(ref) TArray<int32>& array, const FIntegerPredicate& predicate);

	/**
	* Remove element if predicate returns true
	*/
	UFUNCTION(Category = "Utility|Remove If", BlueprintCallable, Meta = (DisplayName = "Remove If Integer64", CompactNodeTitle = "RemoveIf"))
	static UPARAM(DisplayName = ResultArray) TArray<int64>& removeIfInteger64Array(UPARAM(ref) TArray<int64>& array, const FInteger64Predicate& predicate);

	/**
	* Remove element if predicate returns true
	*/
	UFUNCTION(Category = "Utility|Remove If", BlueprintCallable, Meta = (DisplayName = "Remove If Float", CompactNodeTitle = "RemoveIf"))
	static UPARAM(DisplayName = ResultArray) TArray<float>& removeIfFloatArray(UPARAM(ref) TArray<float>& array, const FFloatPredicate& predicate);

	/**
	* Remove element if predicate returns true
	*/
	UFUNCTION(Category = "Utility|Remove If", BlueprintCallable, Meta = (DisplayName = "Remove If String", CompactNodeTitle = "RemoveIf"))
	static UPARAM(DisplayName = ResultArray) TArray<FString>& removeIfStringArray(UPARAM(ref) TArray<FString>& array, const FStringPredicate& predicate);

	/**
	* Remove element if predicate returns true
	*/
	UFUNCTION(Category = "Utility|Remove If", BlueprintCallable, Meta = (DisplayName = "Remove If Name", CompactNodeTitle = "RemoveIf"))
	static UPARAM(DisplayName = ResultArray) TArray<FName>& removeIfNameArray(UPARAM(ref) TArray<FName>& array, const FNamePredicate& predicate);

	/**
	* Remove element if predicate returns true
	*/
	UFUNCTION(Category = "Utility|Remove If", BlueprintCallable, Meta = (DisplayName = "Remove If Text", CompactNodeTitle = "RemoveIf"))
	static UPARAM(DisplayName = ResultArray) TArray<FText>& removeIfTextArray(UPARAM(ref) TArray<FText>& array, const FTextPredicate& predicate);

	/**
	* Remove element if predicate returns true
	*/
	UFUNCTION(Category = "Utility|Remove If", BlueprintCallable, Meta = (DisplayName = "Remove If Object", CompactNodeTitle = "RemoveIf"))
	static UPARAM(DisplayName = ResultArray) TArray<UObject*>& removeIfObjectArray(UPARAM(ref) TArray<UObject*>& array, const FObjectPredicate& predicate);

	/**
	* Remove element if predicate returns true
	*/
	UFUNCTION(Category = "Utility|Remove If", BlueprintCallable, Meta = (DisplayName = "Remove If Object", CompactNodeTitle = "RemoveIf"))
	static UPARAM(DisplayName = ResultArray) TArray<AActor*>& removeIfActorArray(UPARAM(ref) TArray<AActor*>& array, const FActorPredicate& predicate);
#pragma endregion

#pragma region Mapping
#pragma region Integer
	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer-Boolean iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateIntegerBoolean(const TMap<int32, bool>& map, const FIntegerBooleanCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer-Integer iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateIntegerInteger(const TMap<int32, int32>& map, const FIntegerIntegerCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer-Integer64 iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateIntegerInteger64(const TMap<int32, int64>& map, const FIntegerInteger64Callback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer-Float iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateIntegerFloat(const TMap<int32, float>& map, const FIntegerFloatCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer-String iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateIntegerString(const TMap<int32, FString>& map, const FIntegerStringCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer-Name iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateIntegerName(const TMap<int32, FName>& map, const FIntegerNameCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer-Text iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateIntegerText(const TMap<int32, FText>& map, const FIntegerTextCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer-Object iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateIntegerObject(const TMap<int32, UObject*>& map, const FIntegerObjectCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer-Actor iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateIntegerActor(const TMap<int32, AActor*>& map, const FIntegerActorCallback& callback);
#pragma endregion
#pragma region Integer64
	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer64-Boolean iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateInteger64Boolean(const TMap<int64, bool>& map, const FInteger64BooleanCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer64-Integer iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateInteger64Integer(const TMap<int64, int32>& map, const FInteger64IntegerCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer64-Integer64 iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateInteger64Integer64(const TMap<int64, int64>& map, const FInteger64Integer64Callback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer64-Float iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateInteger64Float(const TMap<int64, float>& map, const FInteger64FloatCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer64-String iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateInteger64String(const TMap<int64, FString>& map, const FInteger64StringCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer64-Name iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateInteger64Name(const TMap<int64, FName>& map, const FInteger64NameCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer64-Text iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateInteger64Text(const TMap<int64, FText>& map, const FInteger64TextCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer64-Object iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateInteger64Object(const TMap<int64, UObject*>& map, const FInteger64ObjectCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Integer64-Actor iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateInteger64Actor(const TMap<int64, AActor*>& map, const FInteger64ActorCallback& callback);
#pragma endregion
#pragma region Float
	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Float-Boolean iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateFloatBoolean(const TMap<float, bool>& map, const FFloatBooleanCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Float-Integer iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateFloatInteger(const TMap<float, int32>& map, const FFloatIntegerCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Float-Integer64 iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateFloatInteger64(const TMap<float, int64>& map, const FFloatInteger64Callback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Float-Float iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateFloatFloat(const TMap<float, float>& map, const FFloatFloatCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Float-String iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateFloatString(const TMap<float, FString>& map, const FFloatStringCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Float-Name iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateFloatName(const TMap<float, FName>& map, const FFloatNameCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Float-Text iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateFloatText(const TMap<float, FText>& map, const FFloatTextCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Float-Object iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateFloatObject(const TMap<float, UObject*>& map, const FFloatObjectCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Float-Actor iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateFloatActor(const TMap<float, AActor*>& map, const FFloatActorCallback& callback);
#pragma endregion
#pragma region String
	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped String-Boolean iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateStringBoolean(const TMap<FString, bool>& map, const FStringBooleanCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped String-Integer iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateStringInteger(const TMap<FString, int32>& map, const FStringIntegerCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped String-Integer64 iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateStringInteger64(const TMap<FString, int64>& map, const FStringInteger64Callback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped String-Float iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateStringFloat(const TMap<FString, float>& map, const FStringFloatCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped String-String iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateStringString(const TMap<FString, FString>& map, const FStringStringCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped String-Name iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateStringName(const TMap<FString, FName>& map, const FStringNameCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped String-Text iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateStringText(const TMap<FString, FText>& map, const FStringTextCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped String-Object iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateStringObject(const TMap<FString, UObject*>& map, const FStringObjectCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped String-Actor iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateStringActor(const TMap<FString, AActor*>& map, const FStringActorCallback& callback);
#pragma endregion
#pragma region Name
	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Name-Boolean iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateNameBoolean(const TMap<FName, bool>& map, const FNameBooleanCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Name-Integer iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateNameInteger(const TMap<FName, int32>& map, const FNameIntegerCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Name-Integer64 iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateNameInteger64(const TMap<FName, int64>& map, const FNameInteger64Callback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Name-Float iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateNameFloat(const TMap<FName, float>& map, const FNameFloatCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Name-String iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateNameString(const TMap<FName, FString>& map, const FNameStringCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Name-Name iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateNameName(const TMap<FName, FName>& map, const FNameNameCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Name-Text iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateNameText(const TMap<FName, FText>& map, const FNameTextCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Name-Object iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateNameObject(const TMap<FName, UObject*>& map, const FNameObjectCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Name-Actor iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateNameActor(const TMap<FName, AActor*>& map, const FNameActorCallback& callback);
#pragma endregion
#pragma region Object
	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Boolean iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateObjectBoolean(const TMap<UObject*, bool>& map, const FObjectBooleanCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Integer iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateObjectInteger(const TMap<UObject*, int32>& map, const FObjectIntegerCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Integer64 iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateObjectInteger64(const TMap<UObject*, int64>& map, const FObjectInteger64Callback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Float iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateObjectFloat(const TMap<UObject*, float>& map, const FObjectFloatCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-String iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateObjectString(const TMap<UObject*, FString>& map, const FObjectStringCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Name iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateObjectName(const TMap<UObject*, FName>& map, const FObjectNameCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Text iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateObjectText(const TMap<UObject*, FText>& map, const FObjectTextCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Object iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateObjectObject(const TMap<UObject*, UObject*>& map, const FObjectObjectCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Actor iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateObjectActor(const TMap<UObject*, AActor*>& map, const FObjectActorCallback& callback);
#pragma endregion
#pragma region Actor
	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Boolean iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateActorBoolean(const TMap<AActor*, bool>& map, const FActorBooleanCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Integer iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateActorInteger(const TMap<AActor*, int32>& map, const FActorIntegerCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Integer64 iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateActorInteger64(const TMap<AActor*, int64>& map, const FActorInteger64Callback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Float iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateActorFloat(const TMap<AActor*, float>& map, const FActorFloatCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-String iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateActorString(const TMap<AActor*, FString>& map, const FActorStringCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Name iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateActorName(const TMap<AActor*, FName>& map, const FActorNameCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Text iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateActorText(const TMap<AActor*, FText>& map, const FActorTextCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Object iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateActorObject(const TMap<AActor*, UObject*>& map, const FActorObjectCallback& callback);

	/**
	* Iterate Map
	*/
	UFUNCTION(Category = "Utility|Mapping", BlueprintCallable, Meta = (DisplayName = "Mapped Object-Actor iteration", CompactNodeTitle = "Map Iteration"))
	static void iterateActorActor(const TMap<AActor*, AActor*>& map, const FActorActorCallback& callback);
#pragma endregion
#pragma endregion

#pragma region Replace
	/**
	* Replace one Integer to another
	*/
	UFUNCTION(Category = "Utility|Replace", BlueprintCallable, Meta = (DisplayName = "Replace Integer", CompactNodeTitle = "Replace"))
	static UPARAM(DisplayName = ResultArray) TArray<int32>& replaceIntegerArray(UPARAM(ref) TArray<int32>& array, int32 oldValue, int32 newValue);

	/** 
	* Replace one Integer64 to another
	*/
	UFUNCTION(Category = "Utility|Replace", BlueprintCallable, Meta = (DisplayName = "Replace Integer64", CompactNodeTitle = "Replace"))
	static UPARAM(DisplayName = ResultArray) TArray<int64>& replaceInteger64Array(UPARAM(ref) TArray<int64>& array, int64 oldValue, int64 newValue);

	/** 
	* Replace one Float to another 
	*/
	UFUNCTION(Category = "Utility|Replace", BlueprintCallable, Meta = (DisplayName = "Replace Float", CompactNodeTitle = "Replace"))
	static UPARAM(DisplayName = ResultArray) TArray<float>& replaceFloatArray(UPARAM(ref) TArray<float>& array, float oldValue, float newValue);

	/** 
	* Replace one String to another 
	*/
	UFUNCTION(Category = "Utility|Replace", BlueprintCallable, Meta = (DisplayName = "Replace String", CompactNodeTitle = "Replace"))
	static UPARAM(DisplayName = ResultArray) TArray<FString>& replaceStringArray(UPARAM(ref) TArray<FString>& array, const FString& oldValue, const FString& newValue);

	/**
	* Replace one Name to another
	*/
	UFUNCTION(Category = "Utility|Replace", BlueprintCallable, Meta = (DisplayName = "Replace Name", CompactNodeTitle = "Replace"))
	static UPARAM(DisplayName = ResultArray) TArray<FName>& replaceNameArray(UPARAM(ref) TArray<FName>& array, const FName& oldValue, const FName& newValue);
#pragma endregion

#pragma region ReplaceIf
	/**
	* Replace one Integer to another with predicate
	*/
	UFUNCTION(Category = "Utility|Replace", BlueprintCallable, Meta = (DisplayName = "Replace Integer If", CompactNodeTitle = "Replace If"))
	static UPARAM(DisplayName = ResultArray) TArray<int32>& replaceIfIntegerArray(UPARAM(ref) TArray<int32>& array, int32 newValue, const FIntegerPredicate& predicate);

	/**
	* Replace one Integer64 to another with predicate
	*/
	UFUNCTION(Category = "Utility|Replace", BlueprintCallable, Meta = (DisplayName = "Replace Integer64 If", CompactNodeTitle = "Replace If"))
	static UPARAM(DisplayName = ResultArray) TArray<int64>& replaceIfInteger64Array(UPARAM(ref) TArray<int64>& array, int64 newValue, const FInteger64Predicate& predicate);

	/** 
	* Replace one Float to another with predicate
	*/
	UFUNCTION(Category = "Utility|Replace", BlueprintCallable, Meta = (DisplayName = "Replace Float If", CompactNodeTitle = "Replace If"))
	static UPARAM(DisplayName = ResultArray) TArray<float>& replaceIfFloatArray(UPARAM(ref) TArray<float>& array, float newValue, const FFloatPredicate& predicate);

	/**
	* Replace one String to another with predicate
	*/
	UFUNCTION(Category = "Utility|Replace", BlueprintCallable, Meta = (DisplayName = "Replace String If", CompactNodeTitle = "Replace If"))
	static UPARAM(DisplayName = ResultArray) TArray<FString>& replaceIfStringArray(UPARAM(ref) TArray<FString>& array, const FString& newValue, const FStringPredicate& predicate);

	/**
	* Replace one Name to another with predicate
	*/
	UFUNCTION(Category = "Utility|Replace", BlueprintCallable, Meta = (DisplayName = "Replace Name If", CompactNodeTitle = "Replace If"))
	static UPARAM(DisplayName = ResultArray) TArray<FName>& replaceIfNameArray(UPARAM(ref) TArray<FName>& array, const FName& newValue, const FNamePredicate& predicate);
#pragma endregion

#pragma region Accumulate
	/**
	* Accumulate elements
	*/
	UFUNCTION(Category = "Utility|Accumulate", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Accumulate Integer with Integer Array", CompactNodeTitle = "Accumulate"))
	static UPARAM(DisplayName = AccumulateResult) int32 accumulateIntegerWithIntegerArray(const TArray<int32>& array, int32 init = 0);

	/**
	* Accumulate elements
	*/
	UFUNCTION(Category = "Utility|Accumulate", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Accumulate Integer with Integer64 Array", CompactNodeTitle = "Accumulate"))
	static UPARAM(DisplayName = AccumulateResult) int32 accumulateIntegerWithInteger64Array(const TArray<int64>& array, int32 init = 0);

	/**
	* Accumulate elements
	*/
	UFUNCTION(Category = "Utility|Accumulate", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Accumulate Integer with Float Array", CompactNodeTitle = "Accumulate"))
	static UPARAM(DisplayName = AccumulateResult) int32 accumulateIntegerWithFloatArray(const TArray<float>& array, int32 init = 0);

	/** Accumulate elements */
	UFUNCTION(Category = "Utility|Accumulate", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Accumulate Integer64 with Integer Array", CompactNodeTitle = "Accumulate"))
	static UPARAM(DisplayName = AccumulateResult) int64 accumulateInteger64WithIntegerArray(const TArray<int32>& array, int64 init = 0);

	/** 
	* Accumulate elements
	*/
	UFUNCTION(Category = "Utility|Accumulate", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Accumulate Integer64 with Integer64 Array", CompactNodeTitle = "Accumulate"))
	static UPARAM(DisplayName = AccumulateResult) int64 accumulateInteger64WithInteger64Array(const TArray<int64>& array, int64 init = 0);

	/** Accumulate elements */
	UFUNCTION(Category = "Utility|Accumulate", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Accumulate Integer64 with Float Array", CompactNodeTitle = "Accumulate"))
	static UPARAM(DisplayName = AccumulateResult) int64 accumulateInteger64WithFloatArray(const TArray<float>& array, int64 init = 0);

	/** 
	* Accumulate elements 
	*/
	UFUNCTION(Category = "Utility|Accumulate", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Accumulate Float with Integer Array", CompactNodeTitle = "Accumulate"))
	static UPARAM(DisplayName = AccumulateResult) float accumulateFloatWithIntegerArray(const TArray<int32>& array, float init = 0.0f);

	/**
	* Accumulate elements 
	*/
	UFUNCTION(Category = "Utility|Accumulate", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Accumulate Float with Integer64 Array", CompactNodeTitle = "Accumulate"))
	static UPARAM(DisplayName = AccumulateResult) float accumulateFloatWithInteger64Array(const TArray<int64>& array, float init = 0.0f);

	/**
	* Accumulate elements 
	*/
	UFUNCTION(Category = "Utility|Accumulate", BlueprintCallable, BlueprintPure, Meta = (DisplayName = "Accumulate Float with Float Array", CompactNodeTitle = "Accumulate"))
	static UPARAM(DisplayName = AccumulateResult) float accumulateFloatWithFloatArray(const TArray<float>& array, float init = 0.0f);
#pragma endregion

#pragma region Count
	/**
	* Count entries of given value 
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Count"))
	static UPARAM(DisplayName = CountResult) int32 countIntegers(const TArray<int32>& array, int32 valueToCompare);

	/**
	* Count entries of given value 
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Count"))
	static UPARAM(DisplayName = CountResult) int32 countIntegers64(const TArray<int64>& array, int64 valueToCompare);

	/**
	* Count entries of given value
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Count"))
	static UPARAM(DisplayName = CountResult) int32 countFloats(const TArray<float>& array, float valueToCompare);

	/**
	* Count entries of given value
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Count"))
	static UPARAM(DisplayName = CountResult) int32 countStrings(const TArray<FString>& array, const FString& valueToCompare);

	/**
	* Count entries of given value
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Count"))
	static UPARAM(DisplayName = CountResult) int32 countNames(const TArray<FName>& array, const FName& valueToCompare);
#pragma endregion

#pragma region CountIf
	/**
	* Count entries of values that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CountIf"))
	static UPARAM(DisplayName = CountResult) int32 countIfIntegers(const TArray<int32>& array, const FIntegerPredicate& predicate);

	/**
	* Count entries of values that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CountIf"))
	static UPARAM(DisplayName = CountResult) int32 countIfIntegers64(const TArray<int64>& array, const FInteger64Predicate& predicate);

	/**
	* Count entries of values that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CountIf"))
	static UPARAM(DisplayName = CountResult) int32 countIfFloats(const TArray<float>& array, const FFloatPredicate& predicate);

	/**
	* Count entries of values that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CountIf"))
	static UPARAM(DisplayName = CountResult) int32 countIfStrings(const TArray<FString>& array, const FStringPredicate& predicate);

	/**
	* Count entries of values that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CountIf"))
	static UPARAM(DisplayName = CountResult) int32 countIfNames(const TArray<FName>& array, const FNamePredicate& predicate);

	/**
	* Count entries of values that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CountIf"))
	static UPARAM(DisplayName = CountResult) int32 countIfTexts(const TArray<FText>& array, const FTextPredicate& predicate);

	/**
	* Count entries of values that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CountIf"))
	static UPARAM(DisplayName = CountResult) int32 countIfObjects(const TArray<UObject*>& array, const FObjectPredicate& predicate);

	/**
	* Count entries of values that returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Count", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CountIf"))
	static UPARAM(DisplayName = CountResult) int32 countIfActors(const TArray<AActor*>& array, const FActorPredicate& predicate);
#pragma endregion

#pragma region Copy
	/** 
	* Copy Array
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewArray) TArray<bool> copyBooleanArray(const TArray<bool>& array);

	/**
	* Copy Array
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewArray) TArray<int32> copyIntegerArray(const TArray<int32>& array);

	/**
	* Copy Array
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewArray) TArray<int64> copyInteger64Array(const TArray<int64>& array);

	/**
	* Copy Array
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewArray) TArray<float> copyFloatArray(const TArray<float>& array);

	/**
	* Copy Array
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewArray) TArray<FString> copyStringArray(const TArray<FString>& array);

	/**
	* Copy Array
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewArray) TArray<FName> copyNameArray(const TArray<FName>& array);

	/**
	* Copy Array
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewArray) TArray<FText> copyTextArray(const TArray<FText>& array);

	/**
	* Copy Array
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewArray) TArray<UObject*> copyObjectArray(const TArray<UObject*>& array);

	/**
	* Copy Array
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewArray) TArray<AActor*> copyActorArray(const TArray<AActor*>& array);

	/** 
	* Copy Set 
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewSet) TSet<int32> copyIntegerSet(const TSet<int32>& set);

	/**
	* Copy Set
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewSet) TSet<int64> copyInteger64Set(const TSet<int64>& set);

	/**
	* Copy Set
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewSet) TSet<float> copyFloatSet(const TSet<float>& set);

	/**
	* Copy Set
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewSet) TSet<FString> copyStringSet(const TSet<FString>& set);

	/**
	* Copy Set
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewSet) TSet<FName> copyNameSet(const TSet<FName>& set);

	/**
	* Copy Set
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewSet) TSet<UObject*> copyObjectSet(const TSet<UObject*>& set);

	/**
	* Copy Set
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewSet) TSet<AActor*> copyActorSet(const TSet<AActor*>& set);

#pragma region CopyMapInteger
	/**
	* Copy Map 
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int32, bool> copyMapIntegerBoolean(const TMap<int32, bool>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int32, int32> copyMapIntegerInteger(const TMap<int32, int32>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int32, int64> copyMapIntegerInteger64(const TMap<int32, int64>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int32, float> copyMapIntegerFloat(const TMap<int32, float>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int32, FString> copyMapIntegerString(const TMap<int32, FString>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int32, FName> copyMapIntegerName(const TMap<int32, FName>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int32, FText> copyMapIntegerText(const TMap<int32, FText>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int32, UObject*> copyMapIntegerObject(const TMap<int32, UObject*>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int32, AActor*> copyMapIntegerAActor(const TMap<int32, AActor*>& map);
#pragma endregion

#pragma region CopyMapInteger64
	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int64, bool> copyMapInteger64Boolean(const TMap<int64, bool>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int64, int32> copyMapInteger64Integer(const TMap<int64, int32>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int64, int64> copyMapInteger64Integer64(const TMap<int64, int64>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int64, float> copyMapInteger64Float(const TMap<int64, float>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int64, FString> copyMapInteger64String(const TMap<int64, FString>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int64, FName> copyMapInteger64Name(const TMap<int64, FName>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int64, FText> copyMapInteger64Text(const TMap<int64, FText>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int64, UObject*> copyMapInteger64Object(const TMap<int64, UObject*>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<int64, AActor*> copyMapInteger64Actor(const TMap<int64, AActor*>& map);
#pragma endregion

#pragma region CopyMapFloat
	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<float, bool> copyMapFloatBoolean(const TMap<float, bool>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<float, int32> copyMapFloatInteger(const TMap<float, int32>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<float, int64> copyMapFloatInteger64(const TMap<float, int64>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<float, float> copyMapFloatFloat(const TMap<float, float>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<float, FString> copyMapFloatString(const TMap<float, FString>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<float, FName> copyMapFloatName(const TMap<float, FName>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<float, FText> copyMapFloatText(const TMap<float, FText>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<float, UObject*> copyMapFloatObject(const TMap<float, UObject*>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<float, AActor*> copyMapFloatActor(const TMap<float, AActor*>& map);
#pragma endregion

#pragma region CopyMapString
	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FString, bool> copyMapStringBoolean(const TMap<FString, bool>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FString, int32> copyMapStringInteger(const TMap<FString, int32>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FString, int64> copyMapStringInteger64(const TMap<FString, int64>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FString, float> copyMapStringFloat(const TMap<FString, float>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FString, FString> copyMapStringString(const TMap<FString, FString>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FString, FName> copyMapStringName(const TMap<FString, FName>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FString, FText> copyMapStringText(const TMap<FString, FText>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FString, UObject*> copyMapStringObject(const TMap<FString, UObject*>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FString, AActor*> copyMapStringActor(const TMap<FString, AActor*>& map);
#pragma endregion

#pragma region CopyMapName
	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FName, bool> copyMapNameBoolean(const TMap<FName, bool>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FName, int32> copyMapNameInteger(const TMap<FName, int32>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FName, int64> copyMapNameInteger64(const TMap<FName, int64>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FName, float> copyMapNameFloat(const TMap<FName, float>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FName, FString> copyMapNameString(const TMap<FName, FString>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FName, FName> copyMapNameName(const TMap<FName, FName>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FName, FText> copyMapNameText(const TMap<FName, FText>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FName, UObject*> copyMapNameObject(const TMap<FName, UObject*>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<FName, AActor*> copyMapNameActor(const TMap<FName, AActor*>& map);
#pragma endregion

#pragma region CopyMapObject
	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, bool> copyMapObjectBoolean(const TMap<UObject*, bool>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, int32> copyMapObjectInteger(const TMap<UObject*, int32>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, int64> copyMapObjectInteger64(const TMap<UObject*, int64>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, float> copyMapObjectFloat(const TMap<UObject*, float>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, FString> copyMapObjectString(const TMap<UObject*, FString>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, FName> copyMapObjectName(const TMap<UObject*, FName>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, FText> copyMapObjectText(const TMap<UObject*, FText>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, UObject*> copyMapObjectObject(const TMap<UObject*, UObject*>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, AActor*> copyMapObjectActor(const TMap<UObject*, AActor*>& map);
#pragma endregion

#pragma region CopyMapActor
	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, bool> copyMapActorBoolean(const TMap<AActor*, bool>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, int32> copyMapActorInteger(const TMap<AActor*, int32>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, int64> copyMapActorInteger64(const TMap<AActor*, int64>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, float> copyMapActorFloat(const TMap<AActor*, float>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, FString> copyMapActorString(const TMap<AActor*, FString>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, FName> copyMapActorName(const TMap<AActor*, FName>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, FText> copyMapActorText(const TMap<AActor*, FText>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, UObject*> copyMapActorObject(const TMap<AActor*, UObject*>& map);

	/**
	* Copy Map
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "Copy"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, AActor*> copyMapActorActor(const TMap<AActor*, AActor*>& map);
#pragma endregion
#pragma endregion

#pragma region CopyIf
	/**
	* Copy Array value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewArray) TArray<bool> copyIfBooleanArray(const TArray<bool>& array, const FBooleanPredicate& predicate);

	/**
	* Copy Array value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewArray) TArray<int32> copyIfIntegerArray(const TArray<int32>& array, const FIntegerPredicate& predicate);

	/**
	* Copy Array value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewArray) TArray<int64> copyIfInteger64Array(const TArray<int64>& array, const FInteger64Predicate& predicate);

	/**
	* Copy Array value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewArray) TArray<float> copyIfFloatArray(const TArray<float>& array, const FFloatPredicate& predicate);

	/**
	* Copy Array value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewArray) TArray<FString> copyIfStringArray(const TArray<FString>& array, const FStringPredicate& predicate);

	/**
	* Copy Array value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewArray) TArray<FName> copyIfNameArray(const TArray<FName>& array, const FNamePredicate& predicate);

	/**
	* Copy Array value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewArray) TArray<FText> copyIfTextArray(const TArray<FText>& array, const FTextPredicate& predicate);

	/**
	* Copy Array value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewArray) TArray<UObject*> copyIfObjectArray(const TArray<UObject*>& array, const FObjectPredicate& predicate);

	/**
	* Copy Array value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewArray) TArray<AActor*> copyIfActorArray(const TArray<AActor*>& array, const FActorPredicate& predicate);

	/**
	* Copy Set value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewSet) TSet<int32> copyIfIntegerSet(const TSet<int32>& set, const FIntegerPredicate& predicate);

	/**
	* Copy Set value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewSet) TSet<int64> copyIfInteger64Set(const TSet<int64>& set, const FInteger64Predicate& predicate);

	/**
	* Copy Set value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewSet) TSet<float> copyIfFloatSet(const TSet<float>& set, const FFloatPredicate& predicate);

	/**
	* Copy Set value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewSet) TSet<FString> copyIfStringSet(const TSet<FString>& set, const FStringPredicate& predicate);

	/**
	* Copy Set value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewSet) TSet<FName> copyIfNameSet(const TSet<FName>& set, const FNamePredicate& predicate);

	/**
	* Copy Set value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewSet) TSet<UObject*> copyIfObjectSet(const TSet<UObject*>& set, const FObjectPredicate& predicate);

	/**
	* Copy Set value if value returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewSet) TSet<AActor*> copyIfActorSet(const TSet<AActor*>& set, const FActorPredicate& predicate);

#pragma region CopyIfMapInteger
	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int32, bool> copyIfMapIntegerBoolean(const TMap<int32, bool>& map, const FIntegerBooleanPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int32, int32> copyIfMapIntegerInteger(const TMap<int32, int32>& map, const FIntegerIntegerPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int32, int64> copyIfMapIntegerInteger64(const TMap<int32, int64>& map, const FIntegerInteger64Predicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int32, float> copyIfMapIntegerFloat(const TMap<int32, float>& map, const FIntegerFloatPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int32, FString> copyIfMapIntegerString(const TMap<int32, FString>& map, const FIntegerStringPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int32, FName> copyIfMapIntegerName(const TMap<int32, FName>& map, const FIntegerNamePredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int32, FText> copyIfMapIntegerText(const TMap<int32, FText>& map, const FIntegerTextPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int32, UObject*> copyIfMapIntegerObject(const TMap<int32, UObject*>& map, const FIntegerObjectPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int32, AActor*> copyIfMapIntegerActor(const TMap<int32, AActor*>& map, const FIntegerActorPredicate& predicate);
#pragma endregion

#pragma region CopyIfMapInteger64
	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int64, bool> copyIfMapInteger64Boolean(const TMap<int64, bool>& map, const FInteger64BooleanPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int64, int32> copyIfMapInteger64Integer(const TMap<int64, int32>& map, const FInteger64IntegerPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int64, int64> copyIfMapInteger64Integer64(const TMap<int64, int64>& map, const FInteger64Integer64Predicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int64, float> copyIfMapInteger64Float(const TMap<int64, float>& map, const FInteger64FloatPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int64, FString> copyIfMapInteger64String(const TMap<int64, FString>& map, const FInteger64StringPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int64, FName> copyIfMapInteger64Name(const TMap<int64, FName>& map, const FInteger64NamePredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int64, FText> copyIfMapInteger64Text(const TMap<int64, FText>& map, const FInteger64TextPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int64, UObject*> copyIfMapInteger64Object(const TMap<int64, UObject*>& map, const FInteger64ObjectPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<int64, AActor*> copyIfMapInteger64Actor(const TMap<int64, AActor*>& map, const FInteger64ActorPredicate& predicate);
#pragma endregion

#pragma region CopyIfMapFloat
	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<float, bool> copyIfMapFloatBoolean(const TMap<float, bool>& map, const FFloatBooleanPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<float, int32> copyIfMapFloatInteger(const TMap<float, int32>& map, const FFloatIntegerPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<float, int64> copyIfMapFloatInteger64(const TMap<float, int64>& map, const FFloatInteger64Predicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<float, float> copyIfMapFloatFloat(const TMap<float, float>& map, const FFloatFloatPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<float, FString> copyIfMapFloatString(const TMap<float, FString>& map, const FFloatStringPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<float, FName> copyIfMapFloatName(const TMap<float, FName>& map, const FFloatNamePredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<float, FText> copyIfMapFloatText(const TMap<float, FText>& map, const FFloatTextPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<float, UObject*> copyIfMapFloatObject(const TMap<float, UObject*>& map, const FFloatObjectPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<float, AActor*> copyIfMapFloatActor(const TMap<float, AActor*>& map, const FFloatActorPredicate& predicate);
#pragma endregion

#pragma region CopyIfMapString
	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FString, bool> copyIfMapStringBoolean(const TMap<FString, bool>& map, const FStringBooleanPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FString, int32> copyIfMapStringInteger(const TMap<FString, int32>& map, const FStringIntegerPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FString, int64> copyIfMapStringInteger64(const TMap<FString, int64>& map, const FStringInteger64Predicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FString, float> copyIfMapStringFloat(const TMap<FString, float>& map, const FStringFloatPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FString, FString> copyIfMapStringString(const TMap<FString, FString>& map, const FStringStringPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FString, FName> copyIfMapStringName(const TMap<FString, FName>& map, const FStringNamePredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FString, FText> copyIfMapStringText(const TMap<FString, FText>& map, const FStringTextPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FString, UObject*> copyIfMapStringObject(const TMap<FString, UObject*>& map, const FStringObjectPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FString, AActor*> copyIfMapStringActor(const TMap<FString, AActor*>& map, const FStringActorPredicate& predicate);
#pragma endregion

#pragma region CopyIfMapName
	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FName, bool> copyIfMapNameBoolean(const TMap<FName, bool>& map, const FNameBooleanPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FName, int32> copyIfMapNameInteger(const TMap<FName, int32>& map, const FNameIntegerPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FName, int64> copyIfMapNameInteger64(const TMap<FName, int64>& map, const FNameInteger64Predicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FName, float> copyIfMapNameFloat(const TMap<FName, float>& map, const FNameFloatPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FName, FString> copyIfMapNameString(const TMap<FName, FString>& map, const FNameStringPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FName, FName> copyIfMapNameName(const TMap<FName, FName>& map, const FNameNamePredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FName, FText> copyIfMapNameText(const TMap<FName, FText>& map, const FNameTextPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FName, UObject*> copyIfMapNameObject(const TMap<FName, UObject*>& map, const FNameObjectPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<FName, AActor*> copyIfMapNameActor(const TMap<FName, AActor*>& map, const FNameActorPredicate& predicate);
#pragma endregion

#pragma region CopyIfMapObject
	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, bool> copyIfMapObjectBoolean(const TMap<UObject*, bool>& map, const FObjectBooleanPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, int32> copyIfMapObjectInteger(const TMap<UObject*, int32>& map, const FObjectIntegerPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, int64> copyIfMapObjectInteger64(const TMap<UObject*, int64>& map, const FObjectInteger64Predicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, float> copyIfMapObjectFloat(const TMap<UObject*, float>& map, const FObjectFloatPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, FString> copyIfMapObjectString(const TMap<UObject*, FString>& map, const FObjectStringPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, FName> copyIfMapObjectName(const TMap<UObject*, FName>& map, const FObjectNamePredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, FText> copyIfMapObjectText(const TMap<UObject*, FText>& map, const FObjectTextPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, UObject*> copyIfMapObjectObject(const TMap<UObject*, UObject*>& map, const FObjectObjectPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<UObject*, AActor*> copyIfMapObjectActor(const TMap<UObject*, AActor*>& map, const FObjectActorPredicate& predicate);
#pragma endregion
#pragma region CopyIfMapActor
	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, bool> copyIfMapActorBoolean(const TMap<AActor*, bool>& map, const FActorBooleanPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, int32> copyIfMapActorInteger(const TMap<AActor*, int32>& map, const FActorIntegerPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, int64> copyIfMapActorInteger64(const TMap<AActor*, int64>& map, const FActorInteger64Predicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, float> copyIfMapActorFloat(const TMap<AActor*, float>& map, const FActorFloatPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, FString> copyIfMapActorString(const TMap<AActor*, FString>& map, const FActorStringPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, FName> copyIfMapActorName(const TMap<AActor*, FName>& map, const FActorNamePredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, FText> copyIfMapActorText(const TMap<AActor*, FText>& map, const FActorTextPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, UObject*> copyIfMapActorObject(const TMap<AActor*, UObject*>& map, const FActorObjectPredicate& predicate);

	/**
	* Copy Map key-value pair if pair returns true in predicate
	*/
	UFUNCTION(Category = "Utility|Copy", BlueprintCallable, BlueprintPure, Meta = (CompactNodeTitle = "CopyIf"))
	static UPARAM(DisplayName = NewMap) TMap<AActor*, AActor*> copyIfMapActorActor(const TMap<AActor*, AActor*>& map, const FActorActorPredicate& predicate);
#pragma endregion
#pragma endregion
};
