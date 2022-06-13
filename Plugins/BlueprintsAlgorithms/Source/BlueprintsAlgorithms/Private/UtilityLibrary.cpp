// Copyright (c) 2022 Arkadiy Zakharov

#include "UtilityLibrary.h"

#include "Engine/World.h"
#include "Algo/ForEach.h"
#include "Algo/RemoveIf.h"
#include "Algo/Replace.h"
#include "Algo/Accumulate.h"
#include "Algo/Count.h"
#include "Algo/Copy.h"

template<typename T, typename CallableT>
static TArray<T>& forEach(TArray<T>& array, const CallableT& callable)
{
	if (!callable.IsBound())
	{
		return array;
	}

	Algo::ForEach(array, [&callable](T& value) { callable.Execute(value); });

	return array;
}

template<typename T, typename CallableT, typename PredicateT>
static TArray<T>& forEachIf(TArray<T>& array, const CallableT& callable, const PredicateT& predicate)
{
	if (!callable.IsBound() || !predicate.IsBound())
	{
		return array;
	}

	Algo::ForEachIf
	(
		array,
		[&predicate](const T& value) { return predicate.Execute(value); },
		[&callable](T& value) { callable.Execute(value); }
	);

	return array;
}

template<typename T, typename PredicateT>
static TArray<T>& removeIf(TArray<T>& array, const PredicateT& predicate)
{
	if (!predicate.IsBound())
	{
		return array;
	}

	while (true)
	{
		int32 index = array.IndexOfByPredicate([&predicate](const T& value) { return predicate.Execute(value); });

		if (index == INDEX_NONE)
		{
			break;
		}

		array.RemoveAt(index);
	}

	return array;
}

template<typename KeyT, typename ValueT, typename CallbackT>
static void iterateMap(const TMap<KeyT, ValueT>& map, const CallbackT& callback)
{
	if (!callback.IsBound())
	{
		return;
	}

	for (const auto& data : map)
	{
		callback.Execute(data.Key, data.Value);
	}
}

template<typename T>
static void replace(TArray<T>& array, const T& oldValue, const T& newValue)
{
	Algo::Replace(array, oldValue, newValue);
}

template<typename T, typename PredicateT>
static void replaceIf(TArray<T>& array, const T& newValue, const PredicateT& predicate)
{
	if (!predicate.IsBound())
	{
		return;
	}

	Algo::ReplaceIf(array, [&predicate](const T& value) { return predicate.Execute(value); }, newValue);
}

template<typename T, typename U>
static U accumulate(const TArray<T>& array, const U& init)
{
	return init + StaticCast<U>(Algo::Accumulate(array, StaticCast<T>(0)));
}

template<typename T>
static int32 count(const TArray<T>& array, const T& valueToCompare)
{
	return Algo::Count(array, valueToCompare);
}

template<typename T, typename PredicateT>
static int32 countIf(const TArray<T>& array, const PredicateT& predicate)
{
	return Algo::CountIf(array, [&predicate](const T& value) { return predicate.Execute(value); });
}

template<typename T>
static TArray<T> copy(const TArray<T>& array)
{
	TArray<T> result;

	result.Reserve(array.Num());

	Algo::Copy(array, result);

	return result;
}

template<typename T>
static TSet<T> copy(const TSet<T>& set)
{
	TSet<T> result;

	result.Reserve(set.Num());

	Algo::Copy(set, result);

	return result;
}

template<typename KeyT, typename ValueT>
static TMap<KeyT, ValueT> copy(const TMap<KeyT, ValueT>& map)
{
	TMap<KeyT, ValueT> result;

	result.Append(map);

	return result;
}

template<typename T, typename PredicateT>
static TArray<T> copyIf(const TArray<T>& array, const PredicateT& predicate)
{
	TArray<T> result;

	result.Reserve(array.Num());

	Algo::CopyIf(array, result, [&predicate](const T& value) { return predicate.Execute(value); });

	return result;
}

template<typename T, typename PredicateT>
static TSet<T> copyIf(const TSet<T>& set, const PredicateT& predicate)
{
	TSet<T> result;

	result.Reserve(set.Num());

	Algo::CopyIf(set, result, [&predicate](const T& value) { return predicate.Execute(value); });

	return result;
}

template<typename KeyT, typename ValueT, typename PredicateT>
static TMap<KeyT, ValueT> copyIf(const TMap<KeyT, ValueT>& map, const PredicateT& predicate)
{
	TMap<KeyT, ValueT> result;

	Algo::CopyIf(map, result, [&predicate](const auto& pair) { return predicate.Execute(pair.Key, pair.Value); });

	return result;
}

#pragma region Spawn
AActor* UUtilityLibrary::spawnActor(TSubclassOf<AActor> actorClass, const FTransform& spawnTransform, const AActor* alreadySpawnedActor, ESpawnActorCollisionHandlingMethod collision)
{
	if (!IsValid(alreadySpawnedActor))
	{
		return nullptr;
	}

	UWorld* world = alreadySpawnedActor->GetWorld();

	if (!world)
	{
		return nullptr;
	}

	FActorSpawnParameters spawnParameters;

	spawnParameters.SpawnCollisionHandlingOverride = collision;

	return world->SpawnActor<AActor>(actorClass, spawnTransform, spawnParameters);
}

AActor* UUtilityLibrary::startSpawnActorDeferred(TSubclassOf<AActor> actorClass, const AActor* alreadySpawnedActor, ESpawnActorCollisionHandlingMethod collision)
{
	if (!IsValid(alreadySpawnedActor))
	{
		return nullptr;
	}

	UWorld* world = alreadySpawnedActor->GetWorld();

	if (!world)
	{
		return nullptr;
	}

	return world->SpawnActorDeferred<AActor>(actorClass, {}, nullptr, nullptr, collision);
}

AActor* UUtilityLibrary::finishSpawnActorDeferred(AActor* notYetSpawnedActor, const FTransform& spawnTransform)
{
	if (!IsValid(notYetSpawnedActor))
	{
		return nullptr;
	}

	notYetSpawnedActor->FinishSpawning(spawnTransform);

	return notYetSpawnedActor;
}
#pragma endregion

TArray<bool>& UUtilityLibrary::forEachBooleanArray(TArray<bool>& array, const FBooleanCallable& callable)
{
	return forEach(array, callable);
}

TArray<int32>& UUtilityLibrary::forEachIntegerArray(TArray<int32>& array, const FIntegerCallable& callable)
{
	return forEach(array, callable);
}

TArray<int64>& UUtilityLibrary::forEachInteger64Array(TArray<int64>& array, const FInteger64Callable& callable)
{
	return forEach(array, callable);
}

TArray<float>& UUtilityLibrary::forEachFloatArray(TArray<float>& array, const FFloatCallable& callable)
{
	return forEach(array, callable);
}

TArray<FString>& UUtilityLibrary::forEachStringArray(TArray<FString>& array, const FStringCallable& callable)
{
	return forEach(array, callable);
}

TArray<FName>& UUtilityLibrary::forEachNameArray(TArray<FName>& array, const FNameCallable& callable)
{
	return forEach(array, callable);
}

TArray<FText>& UUtilityLibrary::forEachTextArray(TArray<FText>& array, const FTextCallable& callable)
{
	return forEach(array, callable);
}

TArray<FVector>& UUtilityLibrary::forEachVectorArray(TArray<FVector>& array, const FVectorCallable& callable)
{
	return forEach(array, callable);
}

TArray<FVector2D>& UUtilityLibrary::forEachVector2DArray(TArray<FVector2D>& array, const FVector2DCallable& callable)
{
	return forEach(array, callable);
}

TArray<FColor>& UUtilityLibrary::forEachColorArray(TArray<FColor>& array, const FColorCallable& callable)
{
	return forEach(array, callable);
}

TArray<FLinearColor>& UUtilityLibrary::forEachLinearColorArray(TArray<FLinearColor>& array, const FLinearColorCallable& callable)
{
	return forEach(array, callable);
}

TArray<UObject*>& UUtilityLibrary::forEachObjectArray(TArray<UObject*>& array, const FObjectCallable& callable)
{
	return forEach(array, callable);
}

TArray<AActor*>& UUtilityLibrary::forEachActorArray(TArray<AActor*>& array, const FActorCallable& callable)
{
	return forEach(array, callable);
}

TArray<bool>& UUtilityLibrary::forEachIfBooleanArray(TArray<bool>& array, const FBooleanCallable& callable, const FBooleanPredicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<int32>& UUtilityLibrary::forEachIfIntegerArray(TArray<int32>& array, const FIntegerCallable& callable, const FIntegerPredicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<int64>& UUtilityLibrary::forEachIfInteger64Array(TArray<int64>& array, const FInteger64Callable& callable, const FInteger64Predicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<float>& UUtilityLibrary::forEachIfFloatArray(TArray<float>& array, const FFloatCallable& callable, const FFloatPredicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<FString>& UUtilityLibrary::forEachIfStringArray(TArray<FString>& array, const FStringCallable& callable, const FStringPredicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<FName>& UUtilityLibrary::forEachIfNameArray(TArray<FName>& array, const FNameCallable& callable, const FNamePredicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<FText>& UUtilityLibrary::forEachIfTextArray(TArray<FText>& array, const FTextCallable& callable, const FTextPredicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<FVector>& UUtilityLibrary::forEachIfVectorArray(TArray<FVector>& array, const FVectorCallable& callable, const FVectorPredicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<FVector2D>& UUtilityLibrary::forEachIfVector2DArray(TArray<FVector2D>& array, const FVector2DCallable& callable, const FVector2DPredicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<FColor>& UUtilityLibrary::forEachIfColorArray(TArray<FColor>& array, const FColorCallable& callable, const FColorPredicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<FLinearColor>& UUtilityLibrary::forEachIfLinearColorArray(TArray<FLinearColor>& array, const FLinearColorCallable& callable, const FLinearColorPredicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<UObject*>& UUtilityLibrary::forEachIfObjectArray(TArray<UObject*>& array, const FObjectCallable& callable, const FObjectPredicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<AActor*>& UUtilityLibrary::forEachIfActorArray(TArray<AActor*>& array, const FActorCallable& callable, const FActorPredicate& predicate)
{
	return forEachIf(array, callable, predicate);
}

TArray<bool>& UUtilityLibrary::removeIfBooleanArray(TArray<bool>& array, const FBooleanPredicate& predicate)
{
	return removeIf(array, predicate);
}

TArray<int32>& UUtilityLibrary::removeIfIntegerArray(TArray<int32>& array, const FIntegerPredicate& predicate)
{
	return removeIf(array, predicate);
}

TArray<int64>& UUtilityLibrary::removeIfInteger64Array(TArray<int64>& array, const FInteger64Predicate& predicate)
{
	return removeIf(array, predicate);
}

TArray<float>& UUtilityLibrary::removeIfFloatArray(TArray<float>& array, const FFloatPredicate& predicate)
{
	return removeIf(array, predicate);
}

TArray<FString>& UUtilityLibrary::removeIfStringArray(TArray<FString>& array, const FStringPredicate& predicate)
{
	return removeIf(array, predicate);
}

TArray<FName>& UUtilityLibrary::removeIfNameArray(TArray<FName>& array, const FNamePredicate& predicate)
{
	return removeIf(array, predicate);
}

TArray<FText>& UUtilityLibrary::removeIfTextArray(TArray<FText>& array, const FTextPredicate& predicate)
{
	return removeIf(array, predicate);
}

TArray<UObject*>& UUtilityLibrary::removeIfObjectArray(TArray<UObject*>& array, const FObjectPredicate& predicate)
{
	return removeIf(array, predicate);
}

TArray<AActor*>& UUtilityLibrary::removeIfActorArray(TArray<AActor*>& array, const FActorPredicate& predicate)
{
	return removeIf(array, predicate);
}

#pragma region Integer
void UUtilityLibrary::iterateIntegerBoolean(const TMap<int32, bool>& map, const FIntegerBooleanCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateIntegerInteger(const TMap<int32, int32>& map, const FIntegerIntegerCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateIntegerInteger64(const TMap<int32, int64>& map, const FIntegerInteger64Callback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateIntegerFloat(const TMap<int32, float>& map, const FIntegerFloatCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateIntegerString(const TMap<int32, FString>& map, const FIntegerStringCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateIntegerName(const TMap<int32, FName>& map, const FIntegerNameCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateIntegerText(const TMap<int32, FText>& map, const FIntegerTextCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateIntegerObject(const TMap<int32, UObject*>& map, const FIntegerObjectCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateIntegerActor(const TMap<int32, AActor*>& map, const FIntegerActorCallback& callback)
{
	iterateMap(map, callback);
}
#pragma endregion

#pragma region Integer64
void UUtilityLibrary::iterateInteger64Boolean(const TMap<int64, bool>& map, const FInteger64BooleanCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateInteger64Integer(const TMap<int64, int32>& map, const FInteger64IntegerCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateInteger64Integer64(const TMap<int64, int64>& map, const FInteger64Integer64Callback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateInteger64Float(const TMap<int64, float>& map, const FInteger64FloatCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateInteger64String(const TMap<int64, FString>& map, const FInteger64StringCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateInteger64Name(const TMap<int64, FName>& map, const FInteger64NameCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateInteger64Text(const TMap<int64, FText>& map, const FInteger64TextCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateInteger64Object(const TMap<int64, UObject*>& map, const FInteger64ObjectCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateInteger64Actor(const TMap<int64, AActor*>& map, const FInteger64ActorCallback& callback)
{
	iterateMap(map, callback);
}
#pragma endregion

#pragma region Float
void UUtilityLibrary::iterateFloatBoolean(const TMap<float, bool>& map, const FFloatBooleanCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateFloatInteger(const TMap<float, int32>& map, const FFloatIntegerCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateFloatInteger64(const TMap<float, int64>& map, const FFloatInteger64Callback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateFloatFloat(const TMap<float, float>& map, const FFloatFloatCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateFloatString(const TMap<float, FString>& map, const FFloatStringCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateFloatName(const TMap<float, FName>& map, const FFloatNameCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateFloatText(const TMap<float, FText>& map, const FFloatTextCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateFloatObject(const TMap<float, UObject*>& map, const FFloatObjectCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateFloatActor(const TMap<float, AActor*>& map, const FFloatActorCallback& callback)
{
	iterateMap(map, callback);
}
#pragma endregion

#pragma region String
void UUtilityLibrary::iterateStringBoolean(const TMap<FString, bool>& map, const FStringBooleanCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateStringInteger(const TMap<FString, int32>& map, const FStringIntegerCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateStringInteger64(const TMap<FString, int64>& map, const FStringInteger64Callback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateStringFloat(const TMap<FString, float>& map, const FStringFloatCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateStringString(const TMap<FString, FString>& map, const FStringStringCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateStringName(const TMap<FString, FName>& map, const FStringNameCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateStringText(const TMap<FString, FText>& map, const FStringTextCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateStringObject(const TMap<FString, UObject*>& map, const FStringObjectCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateStringActor(const TMap<FString, AActor*>& map, const FStringActorCallback& callback)
{
	iterateMap(map, callback);
}
#pragma endregion

#pragma region Name
void UUtilityLibrary::iterateNameBoolean(const TMap<FName, bool>& map, const FNameBooleanCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateNameInteger(const TMap<FName, int32>& map, const FNameIntegerCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateNameInteger64(const TMap<FName, int64>& map, const FNameInteger64Callback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateNameFloat(const TMap<FName, float>& map, const FNameFloatCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateNameString(const TMap<FName, FString>& map, const FNameStringCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateNameName(const TMap<FName, FName>& map, const FNameNameCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateNameText(const TMap<FName, FText>& map, const FNameTextCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateNameObject(const TMap<FName, UObject*>& map, const FNameObjectCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateNameActor(const TMap<FName, AActor*>& map, const FNameActorCallback& callback)
{
	iterateMap(map, callback);
}
#pragma endregion

#pragma region Object
void UUtilityLibrary::iterateObjectBoolean(const TMap<UObject*, bool>& map, const FObjectBooleanCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateObjectInteger(const TMap<UObject*, int32>& map, const FObjectIntegerCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateObjectInteger64(const TMap<UObject*, int64>& map, const FObjectInteger64Callback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateObjectFloat(const TMap<UObject*, float>& map, const FObjectFloatCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateObjectString(const TMap<UObject*, FString>& map, const FObjectStringCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateObjectName(const TMap<UObject*, FName>& map, const FObjectNameCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateObjectText(const TMap<UObject*, FText>& map, const FObjectTextCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateObjectObject(const TMap<UObject*, UObject*>& map, const FObjectObjectCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateObjectActor(const TMap<UObject*, AActor*>& map, const FObjectActorCallback& callback)
{
	iterateMap(map, callback);
}
#pragma endregion

#pragma region Actor
void UUtilityLibrary::iterateActorBoolean(const TMap<AActor*, bool>& map, const FActorBooleanCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateActorInteger(const TMap<AActor*, int32>& map, const FActorIntegerCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateActorInteger64(const TMap<AActor*, int64>& map, const FActorInteger64Callback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateActorFloat(const TMap<AActor*, float>& map, const FActorFloatCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateActorString(const TMap<AActor*, FString>& map, const FActorStringCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateActorName(const TMap<AActor*, FName>& map, const FActorNameCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateActorText(const TMap<AActor*, FText>& map, const FActorTextCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateActorObject(const TMap<AActor*, UObject*>& map, const FActorObjectCallback& callback)
{
	iterateMap(map, callback);
}

void UUtilityLibrary::iterateActorActor(const TMap<AActor*, AActor*>& map, const FActorActorCallback& callback)
{
	iterateMap(map, callback);
}

#pragma endregion

TArray<int32>& UUtilityLibrary::replaceIntegerArray(TArray<int32>& array, int32 oldValue, int32 newValue)
{
	replace(array, oldValue, newValue);

	return array;
}

TArray<int64>& UUtilityLibrary::replaceInteger64Array(TArray<int64>& array, int64 oldValue, int64 newValue)
{
	replace(array, oldValue, newValue);

	return array;
}

TArray<float>& UUtilityLibrary::replaceFloatArray(TArray<float>& array, float oldValue, float newValue)
{
	replace(array, oldValue, newValue);

	return array;
}

TArray<FString>& UUtilityLibrary::replaceStringArray(TArray<FString>& array, const FString& oldValue, const FString& newValue)
{
	replace(array, oldValue, newValue);

	return array;
}

TArray<FName>& UUtilityLibrary::replaceNameArray(TArray<FName>& array, const FName& oldValue, const FName& newValue)
{
	replace(array, oldValue, newValue);

	return array;
}

TArray<int32>& UUtilityLibrary::replaceIfIntegerArray(TArray<int32>& array, int32 newValue, const FIntegerPredicate& predicate)
{
	replaceIf(array, newValue, predicate);

	return array;
}

TArray<int64>& UUtilityLibrary::replaceIfInteger64Array(TArray<int64>& array, int64 newValue, const FInteger64Predicate& predicate)
{
	replaceIf(array, newValue, predicate);

	return array;
}

TArray<float>& UUtilityLibrary::replaceIfFloatArray(TArray<float>& array, float newValue, const FFloatPredicate& predicate)
{
	replaceIf(array, newValue, predicate);

	return array;
}

TArray<FString>& UUtilityLibrary::replaceIfStringArray(TArray<FString>& array, const FString& newValue, const FStringPredicate& predicate)
{
	replaceIf(array, newValue, predicate);

	return array;
}

TArray<FName>& UUtilityLibrary::replaceIfNameArray(TArray<FName>& array, const FName& newValue, const FNamePredicate& predicate)
{
	replaceIf(array, newValue, predicate);

	return array;
}

int32 UUtilityLibrary::accumulateIntegerWithIntegerArray(const TArray<int32>& array, int32 init)
{
	return accumulate(array, init);
}

int32 UUtilityLibrary::accumulateIntegerWithInteger64Array(const TArray<int64>& array, int32 init)
{
	return accumulate(array, init);
}

int32 UUtilityLibrary::accumulateIntegerWithFloatArray(const TArray<float>& array, int32 init)
{
	return accumulate(array, init);
}

int64 UUtilityLibrary::accumulateInteger64WithIntegerArray(const TArray<int32>& array, int64 init)
{
	return accumulate(array, init);
}

int64 UUtilityLibrary::accumulateInteger64WithInteger64Array(const TArray<int64>& array, int64 init)
{
	return accumulate(array, init);
}

int64 UUtilityLibrary::accumulateInteger64WithFloatArray(const TArray<float>& array, int64 init)
{
	return accumulate(array, init);
}

float UUtilityLibrary::accumulateFloatWithIntegerArray(const TArray<int32>& array, float init)
{
	return accumulate(array, init);
}

float UUtilityLibrary::accumulateFloatWithInteger64Array(const TArray<int64>& array, float init)
{
	return accumulate(array, init);
}

float UUtilityLibrary::accumulateFloatWithFloatArray(const TArray<float>& array, float init)
{
	return accumulate(array, init);
}

int32 UUtilityLibrary::countIntegers(const TArray<int32>& array, int32 valueToCompare)
{
	return count(array, valueToCompare);
}

int32 UUtilityLibrary::countIntegers64(const TArray<int64>& array, int64 valueToCompare)
{
	return count(array, valueToCompare);
}

int32 UUtilityLibrary::countFloats(const TArray<float>& array, float valueToCompare)
{
	return count(array, valueToCompare);
}

int32 UUtilityLibrary::countStrings(const TArray<FString>& array, const FString& valueToCompare)
{
	return count(array, valueToCompare);
}

int32 UUtilityLibrary::countNames(const TArray<FName>& array, const FName& valueToCompare)
{
	return count(array, valueToCompare);
}

int32 UUtilityLibrary::countIfIntegers(const TArray<int32>& array, const FIntegerPredicate& predicate)
{
	return countIf(array, predicate);
}

int32 UUtilityLibrary::countIfIntegers64(const TArray<int64>& array, const FInteger64Predicate& predicate)
{
	return countIf(array, predicate);
}

int32 UUtilityLibrary::countIfFloats(const TArray<float>& array, const FFloatPredicate& predicate)
{
	return countIf(array, predicate);
}

int32 UUtilityLibrary::countIfStrings(const TArray<FString>& array, const FStringPredicate& predicate)
{
	return countIf(array, predicate);
}

int32 UUtilityLibrary::countIfNames(const TArray<FName>& array, const FNamePredicate& predicate)
{
	return countIf(array, predicate);
}

int32 UUtilityLibrary::countIfTexts(const TArray<FText>& array, const FTextPredicate& predicate)
{
	return countIf(array, predicate);
}

int32 UUtilityLibrary::countIfObjects(const TArray<UObject*>& array, const FObjectPredicate& predicate)
{
	return countIf(array, predicate);
}

int32 UUtilityLibrary::countIfActors(const TArray<AActor*>& array, const FActorPredicate& predicate)
{
	return countIf(array, predicate);
}

TArray<bool> UUtilityLibrary::copyBooleanArray(const TArray<bool>& array)
{
	return copy(array);
}

TArray<int32> UUtilityLibrary::copyIntegerArray(const TArray<int32>& array)
{
	return copy(array);
}

TArray<int64> UUtilityLibrary::copyInteger64Array(const TArray<int64>& array)
{
	return copy(array);
}

TArray<float> UUtilityLibrary::copyFloatArray(const TArray<float>& array)
{
	return copy(array);
}

TArray<FString> UUtilityLibrary::copyStringArray(const TArray<FString>& array)
{
	return copy(array);
}

TArray<FName> UUtilityLibrary::copyNameArray(const TArray<FName>& array)
{
	return copy(array);
}

TArray<FText> UUtilityLibrary::copyTextArray(const TArray<FText>& array)
{
	return copy(array);
}

TArray<UObject*> UUtilityLibrary::copyObjectArray(const TArray<UObject*>& array)
{
	return copy(array);
}

TArray<AActor*> UUtilityLibrary::copyActorArray(const TArray<AActor*>& array)
{
	return copy(array);
}

TSet<int32> UUtilityLibrary::copyIntegerSet(const TSet<int32>& set)
{
	return copy(set);
}

TSet<int64> UUtilityLibrary::copyInteger64Set(const TSet<int64>& set)
{
	return copy(set);
}

TSet<float> UUtilityLibrary::copyFloatSet(const TSet<float>& set)
{
	return copy(set);
}

TSet<FString> UUtilityLibrary::copyStringSet(const TSet<FString>& set)
{
	return copy(set);
}

TSet<FName> UUtilityLibrary::copyNameSet(const TSet<FName>& set)
{
	return copy(set);
}

TSet<UObject*> UUtilityLibrary::copyObjectSet(const TSet<UObject*>& set)
{
	return copy(set);
}

TSet<AActor*> UUtilityLibrary::copyActorSet(const TSet<AActor*>& set)
{
	return copy(set);
}

#pragma region CopyMapInteger
TMap<int32, bool> UUtilityLibrary::copyMapIntegerBoolean(const TMap<int32, bool>& map)
{
	return copy(map);
}

TMap<int32, int32> UUtilityLibrary::copyMapIntegerInteger(const TMap<int32, int32>& map)
{
	return copy(map);
}

TMap<int32, int64> UUtilityLibrary::copyMapIntegerInteger64(const TMap<int32, int64>& map)
{
	return copy(map);
}

TMap<int32, float> UUtilityLibrary::copyMapIntegerFloat(const TMap<int32, float>& map)
{
	return copy(map);
}

TMap<int32, FString> UUtilityLibrary::copyMapIntegerString(const TMap<int32, FString>& map)
{
	return copy(map);
}

TMap<int32, FName> UUtilityLibrary::copyMapIntegerName(const TMap<int32, FName>& map)
{
	return copy(map);
}

TMap<int32, FText> UUtilityLibrary::copyMapIntegerText(const TMap<int32, FText>& map)
{
	return copy(map);
}

TMap<int32, UObject*> UUtilityLibrary::copyMapIntegerObject(const TMap<int32, UObject*>& map)
{
	return copy(map);
}

TMap<int32, AActor*> UUtilityLibrary::copyMapIntegerAActor(const TMap<int32, AActor*>& map)
{
	return copy(map);
}
#pragma endregion

#pragma region CopyMapInteger64
TMap<int64, bool> UUtilityLibrary::copyMapInteger64Boolean(const TMap<int64, bool>& map)
{
	return copy(map);
}

TMap<int64, int32> UUtilityLibrary::copyMapInteger64Integer(const TMap<int64, int32>& map)
{
	return copy(map);
}

TMap<int64, int64> UUtilityLibrary::copyMapInteger64Integer64(const TMap<int64, int64>& map)
{
	return copy(map);
}

TMap<int64, float> UUtilityLibrary::copyMapInteger64Float(const TMap<int64, float>& map)
{
	return copy(map);
}

TMap<int64, FString> UUtilityLibrary::copyMapInteger64String(const TMap<int64, FString>& map)
{
	return copy(map);
}

TMap<int64, FName> UUtilityLibrary::copyMapInteger64Name(const TMap<int64, FName>& map)
{
	return copy(map);
}

TMap<int64, FText> UUtilityLibrary::copyMapInteger64Text(const TMap<int64, FText>& map)
{
	return copy(map);
}

TMap<int64, UObject*> UUtilityLibrary::copyMapInteger64Object(const TMap<int64, UObject*>& map)
{
	return copy(map);
}

TMap<int64, AActor*> UUtilityLibrary::copyMapInteger64Actor(const TMap<int64, AActor*>& map)
{
	return copy(map);
}
#pragma endregion

#pragma region CopyMapFloat
TMap<float, bool> UUtilityLibrary::copyMapFloatBoolean(const TMap<float, bool>& map)
{
	return copy(map);
}

TMap<float, int32> UUtilityLibrary::copyMapFloatInteger(const TMap<float, int32>& map)
{
	return copy(map);
}

TMap<float, int64> UUtilityLibrary::copyMapFloatInteger64(const TMap<float, int64>& map)
{
	return copy(map);
}

TMap<float, float> UUtilityLibrary::copyMapFloatFloat(const TMap<float, float>& map)
{
	return copy(map);
}

TMap<float, FString> UUtilityLibrary::copyMapFloatString(const TMap<float, FString>& map)
{
	return copy(map);
}

TMap<float, FName> UUtilityLibrary::copyMapFloatName(const TMap<float, FName>& map)
{
	return copy(map);
}

TMap<float, FText> UUtilityLibrary::copyMapFloatText(const TMap<float, FText>& map)
{
	return copy(map);
}

TMap<float, UObject*> UUtilityLibrary::copyMapFloatObject(const TMap<float, UObject*>& map)
{
	return copy(map);
}

TMap<float, AActor*> UUtilityLibrary::copyMapFloatActor(const TMap<float, AActor*>& map)
{
	return copy(map);
}
#pragma endregion

#pragma region CopyMapString
TMap<FString, bool> UUtilityLibrary::copyMapStringBoolean(const TMap<FString, bool>& map)
{
	return copy(map);
}

TMap<FString, int32> UUtilityLibrary::copyMapStringInteger(const TMap<FString, int32>& map)
{
	return copy(map);
}

TMap<FString, int64> UUtilityLibrary::copyMapStringInteger64(const TMap<FString, int64>& map)
{
	return copy(map);
}

TMap<FString, float> UUtilityLibrary::copyMapStringFloat(const TMap<FString, float>& map)
{
	return copy(map);
}

TMap<FString, FString> UUtilityLibrary::copyMapStringString(const TMap<FString, FString>& map)
{
	return copy(map);
}

TMap<FString, FName> UUtilityLibrary::copyMapStringName(const TMap<FString, FName>& map)
{
	return copy(map);
}

TMap<FString, FText> UUtilityLibrary::copyMapStringText(const TMap<FString, FText>& map)
{
	return copy(map);
}

TMap<FString, UObject*> UUtilityLibrary::copyMapStringObject(const TMap<FString, UObject*>& map)
{
	return copy(map);
}

TMap<FString, AActor*> UUtilityLibrary::copyMapStringActor(const TMap<FString, AActor*>& map)
{
	return copy(map);
}
#pragma endregion

#pragma region CopyMapName
TMap<FName, bool> UUtilityLibrary::copyMapNameBoolean(const TMap<FName, bool>& map)
{
	return copy(map);
}

TMap<FName, int32> UUtilityLibrary::copyMapNameInteger(const TMap<FName, int32>& map)
{
	return copy(map);
}

TMap<FName, int64> UUtilityLibrary::copyMapNameInteger64(const TMap<FName, int64>& map)
{
	return copy(map);
}

TMap<FName, float> UUtilityLibrary::copyMapNameFloat(const TMap<FName, float>& map)
{
	return copy(map);
}

TMap<FName, FString> UUtilityLibrary::copyMapNameString(const TMap<FName, FString>& map)
{
	return copy(map);
}

TMap<FName, FName> UUtilityLibrary::copyMapNameName(const TMap<FName, FName>& map)
{
	return copy(map);
}

TMap<FName, FText> UUtilityLibrary::copyMapNameText(const TMap<FName, FText>& map)
{
	return copy(map);
}

TMap<FName, UObject*> UUtilityLibrary::copyMapNameObject(const TMap<FName, UObject*>& map)
{
	return copy(map);
}

TMap<FName, AActor*> UUtilityLibrary::copyMapNameActor(const TMap<FName, AActor*>& map)
{
	return copy(map);
}
#pragma endregion

#pragma region CopyMapObject
TMap<UObject*, bool> UUtilityLibrary::copyMapObjectBoolean(const TMap<UObject*, bool>& map)
{
	return copy(map);
}

TMap<UObject*, int32> UUtilityLibrary::copyMapObjectInteger(const TMap<UObject*, int32>& map)
{
	return copy(map);
}

TMap<UObject*, int64> UUtilityLibrary::copyMapObjectInteger64(const TMap<UObject*, int64>& map)
{
	return copy(map);
}

TMap<UObject*, float> UUtilityLibrary::copyMapObjectFloat(const TMap<UObject*, float>& map)
{
	return copy(map);
}

TMap<UObject*, FString> UUtilityLibrary::copyMapObjectString(const TMap<UObject*, FString>& map)
{
	return copy(map);
}

TMap<UObject*, FName> UUtilityLibrary::copyMapObjectName(const TMap<UObject*, FName>& map)
{
	return copy(map);
}

TMap<UObject*, FText> UUtilityLibrary::copyMapObjectText(const TMap<UObject*, FText>& map)
{
	return copy(map);
}

TMap<UObject*, UObject*> UUtilityLibrary::copyMapObjectObject(const TMap<UObject*, UObject*>& map)
{
	return copy(map);
}

TMap<UObject*, AActor*> UUtilityLibrary::copyMapObjectActor(const TMap<UObject*, AActor*>& map)
{
	return copy(map);
}
#pragma endregion

#pragma region CopyMapActor
TMap<AActor*, bool> UUtilityLibrary::copyMapActorBoolean(const TMap<AActor*, bool>& map)
{
	return copy(map);
}

TMap<AActor*, int32> UUtilityLibrary::copyMapActorInteger(const TMap<AActor*, int32>& map)
{
	return copy(map);
}

TMap<AActor*, int64> UUtilityLibrary::copyMapActorInteger64(const TMap<AActor*, int64>& map)
{
	return copy(map);
}

TMap<AActor*, float> UUtilityLibrary::copyMapActorFloat(const TMap<AActor*, float>& map)
{
	return copy(map);
}

TMap<AActor*, FString> UUtilityLibrary::copyMapActorString(const TMap<AActor*, FString>& map)
{
	return copy(map);
}

TMap<AActor*, FName> UUtilityLibrary::copyMapActorName(const TMap<AActor*, FName>& map)
{
	return copy(map);
}

TMap<AActor*, FText> UUtilityLibrary::copyMapActorText(const TMap<AActor*, FText>& map)
{
	return copy(map);
}

TMap<AActor*, UObject*> UUtilityLibrary::copyMapActorObject(const TMap<AActor*, UObject*>& map)
{
	return copy(map);
}

TMap<AActor*, AActor*> UUtilityLibrary::copyMapActorActor(const TMap<AActor*, AActor*>& map)
{
	return copy(map);
}

#pragma endregion

TArray<bool> UUtilityLibrary::copyIfBooleanArray(const TArray<bool>& array, const FBooleanPredicate& predicate)
{
	return copyIf(array, predicate);
}

TArray<int32> UUtilityLibrary::copyIfIntegerArray(const TArray<int32>& array, const FIntegerPredicate& predicate)
{
	return copyIf(array, predicate);
}

TArray<int64> UUtilityLibrary::copyIfInteger64Array(const TArray<int64>& array, const FInteger64Predicate& predicate)
{
	return copyIf(array, predicate);
}

TArray<float> UUtilityLibrary::copyIfFloatArray(const TArray<float>& array, const FFloatPredicate& predicate)
{
	return copyIf(array, predicate);
}

TArray<FString> UUtilityLibrary::copyIfStringArray(const TArray<FString>& array, const FStringPredicate& predicate)
{
	return copyIf(array, predicate);
}

TArray<FName> UUtilityLibrary::copyIfNameArray(const TArray<FName>& array, const FNamePredicate& predicate)
{
	return copyIf(array, predicate);
}

TArray<FText> UUtilityLibrary::copyIfTextArray(const TArray<FText>& array, const FTextPredicate& predicate)
{
	return copyIf(array, predicate);
}

TArray<UObject*> UUtilityLibrary::copyIfObjectArray(const TArray<UObject*>& array, const FObjectPredicate& predicate)
{
	return copyIf(array, predicate);
}

TArray<AActor*> UUtilityLibrary::copyIfActorArray(const TArray<AActor*>& array, const FActorPredicate& predicate)
{
	return copyIf(array, predicate);
}

TSet<int32> UUtilityLibrary::copyIfIntegerSet(const TSet<int32>& set, const FIntegerPredicate& predicate)
{
	return copyIf(set, predicate);
}

TSet<int64> UUtilityLibrary::copyIfInteger64Set(const TSet<int64>& set, const FInteger64Predicate& predicate)
{
	return copyIf(set, predicate);
}

TSet<float> UUtilityLibrary::copyIfFloatSet(const TSet<float>& set, const FFloatPredicate& predicate)
{
	return copyIf(set, predicate);
}

TSet<FString> UUtilityLibrary::copyIfStringSet(const TSet<FString>& set, const FStringPredicate& predicate)
{
	return copyIf(set, predicate);
}

TSet<FName> UUtilityLibrary::copyIfNameSet(const TSet<FName>& set, const FNamePredicate& predicate)
{
	return copyIf(set, predicate);
}

TSet<UObject*> UUtilityLibrary::copyIfObjectSet(const TSet<UObject*>& set, const FObjectPredicate& predicate)
{
	return copyIf(set, predicate);
}

TSet<AActor*> UUtilityLibrary::copyIfActorSet(const TSet<AActor*>& set, const FActorPredicate& predicate)
{
	return copyIf(set, predicate);
}

#pragma region CopyIfMapInteger
TMap<int32, bool> UUtilityLibrary::copyIfMapIntegerBoolean(const TMap<int32, bool>& map, const FIntegerBooleanPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int32, int32> UUtilityLibrary::copyIfMapIntegerInteger(const TMap<int32, int32>& map, const FIntegerIntegerPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int32, int64> UUtilityLibrary::copyIfMapIntegerInteger64(const TMap<int32, int64>& map, const FIntegerInteger64Predicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int32, float> UUtilityLibrary::copyIfMapIntegerFloat(const TMap<int32, float>& map, const FIntegerFloatPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int32, FString> UUtilityLibrary::copyIfMapIntegerString(const TMap<int32, FString>& map, const FIntegerStringPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int32, FName> UUtilityLibrary::copyIfMapIntegerName(const TMap<int32, FName>& map, const FIntegerNamePredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int32, FText> UUtilityLibrary::copyIfMapIntegerText(const TMap<int32, FText>& map, const FIntegerTextPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int32, UObject*> UUtilityLibrary::copyIfMapIntegerObject(const TMap<int32, UObject*>& map, const FIntegerObjectPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int32, AActor*> UUtilityLibrary::copyIfMapIntegerActor(const TMap<int32, AActor*>& map, const FIntegerActorPredicate& predicate)
{
	return copyIf(map, predicate);
}
#pragma endregion

#pragma region CopyIfMapInteger64
TMap<int64, bool> UUtilityLibrary::copyIfMapInteger64Boolean(const TMap<int64, bool>& map, const FInteger64BooleanPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int64, int32> UUtilityLibrary::copyIfMapInteger64Integer(const TMap<int64, int32>& map, const FInteger64IntegerPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int64, int64> UUtilityLibrary::copyIfMapInteger64Integer64(const TMap<int64, int64>& map, const FInteger64Integer64Predicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int64, float> UUtilityLibrary::copyIfMapInteger64Float(const TMap<int64, float>& map, const FInteger64FloatPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int64, FString> UUtilityLibrary::copyIfMapInteger64String(const TMap<int64, FString>& map, const FInteger64StringPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int64, FName> UUtilityLibrary::copyIfMapInteger64Name(const TMap<int64, FName>& map, const FInteger64NamePredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int64, FText> UUtilityLibrary::copyIfMapInteger64Text(const TMap<int64, FText>& map, const FInteger64TextPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int64, UObject*> UUtilityLibrary::copyIfMapInteger64Object(const TMap<int64, UObject*>& map, const FInteger64ObjectPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<int64, AActor*> UUtilityLibrary::copyIfMapInteger64Actor(const TMap<int64, AActor*>& map, const FInteger64ActorPredicate& predicate)
{
	return copyIf(map, predicate);
}
#pragma endregion

#pragma region CopyIfMapFloat
TMap<float, bool> UUtilityLibrary::copyIfMapFloatBoolean(const TMap<float, bool>& map, const FFloatBooleanPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<float, int32> UUtilityLibrary::copyIfMapFloatInteger(const TMap<float, int32>& map, const FFloatIntegerPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<float, int64> UUtilityLibrary::copyIfMapFloatInteger64(const TMap<float, int64>& map, const FFloatInteger64Predicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<float, float> UUtilityLibrary::copyIfMapFloatFloat(const TMap<float, float>& map, const FFloatFloatPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<float, FString> UUtilityLibrary::copyIfMapFloatString(const TMap<float, FString>& map, const FFloatStringPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<float, FName> UUtilityLibrary::copyIfMapFloatName(const TMap<float, FName>& map, const FFloatNamePredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<float, FText> UUtilityLibrary::copyIfMapFloatText(const TMap<float, FText>& map, const FFloatTextPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<float, UObject*> UUtilityLibrary::copyIfMapFloatObject(const TMap<float, UObject*>& map, const FFloatObjectPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<float, AActor*> UUtilityLibrary::copyIfMapFloatActor(const TMap<float, AActor*>& map, const FFloatActorPredicate& predicate)
{
	return copyIf(map, predicate);
}
#pragma endregion

#pragma region CopyIfMapString
TMap<FString, bool> UUtilityLibrary::copyIfMapStringBoolean(const TMap<FString, bool>& map, const FStringBooleanPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FString, int32> UUtilityLibrary::copyIfMapStringInteger(const TMap<FString, int32>& map, const FStringIntegerPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FString, int64> UUtilityLibrary::copyIfMapStringInteger64(const TMap<FString, int64>& map, const FStringInteger64Predicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FString, float> UUtilityLibrary::copyIfMapStringFloat(const TMap<FString, float>& map, const FStringFloatPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FString, FString> UUtilityLibrary::copyIfMapStringString(const TMap<FString, FString>& map, const FStringStringPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FString, FName> UUtilityLibrary::copyIfMapStringName(const TMap<FString, FName>& map, const FStringNamePredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FString, FText> UUtilityLibrary::copyIfMapStringText(const TMap<FString, FText>& map, const FStringTextPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FString, UObject*> UUtilityLibrary::copyIfMapStringObject(const TMap<FString, UObject*>& map, const FStringObjectPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FString, AActor*> UUtilityLibrary::copyIfMapStringActor(const TMap<FString, AActor*>& map, const FStringActorPredicate& predicate)
{
	return copyIf(map, predicate);
}
#pragma endregion

#pragma region CopyIfMapName
TMap<FName, bool> UUtilityLibrary::copyIfMapNameBoolean(const TMap<FName, bool>& map, const FNameBooleanPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FName, int32> UUtilityLibrary::copyIfMapNameInteger(const TMap<FName, int32>& map, const FNameIntegerPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FName, int64> UUtilityLibrary::copyIfMapNameInteger64(const TMap<FName, int64>& map, const FNameInteger64Predicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FName, float> UUtilityLibrary::copyIfMapNameFloat(const TMap<FName, float>& map, const FNameFloatPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FName, FString> UUtilityLibrary::copyIfMapNameString(const TMap<FName, FString>& map, const FNameStringPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FName, FName> UUtilityLibrary::copyIfMapNameName(const TMap<FName, FName>& map, const FNameNamePredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FName, FText> UUtilityLibrary::copyIfMapNameText(const TMap<FName, FText>& map, const FNameTextPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FName, UObject*> UUtilityLibrary::copyIfMapNameObject(const TMap<FName, UObject*>& map, const FNameObjectPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<FName, AActor*> UUtilityLibrary::copyIfMapNameActor(const TMap<FName, AActor*>& map, const FNameActorPredicate& predicate)
{
	return copyIf(map, predicate);
}
#pragma endregion

#pragma region CopyIfMapObject
TMap<UObject*, bool> UUtilityLibrary::copyIfMapObjectBoolean(const TMap<UObject*, bool>& map, const FObjectBooleanPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<UObject*, int32> UUtilityLibrary::copyIfMapObjectInteger(const TMap<UObject*, int32>& map, const FObjectIntegerPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<UObject*, int64> UUtilityLibrary::copyIfMapObjectInteger64(const TMap<UObject*, int64>& map, const FObjectInteger64Predicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<UObject*, float> UUtilityLibrary::copyIfMapObjectFloat(const TMap<UObject*, float>& map, const FObjectFloatPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<UObject*, FString> UUtilityLibrary::copyIfMapObjectString(const TMap<UObject*, FString>& map, const FObjectStringPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<UObject*, FName> UUtilityLibrary::copyIfMapObjectName(const TMap<UObject*, FName>& map, const FObjectNamePredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<UObject*, FText> UUtilityLibrary::copyIfMapObjectText(const TMap<UObject*, FText>& map, const FObjectTextPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<UObject*, UObject*> UUtilityLibrary::copyIfMapObjectObject(const TMap<UObject*, UObject*>& map, const FObjectObjectPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<UObject*, AActor*> UUtilityLibrary::copyIfMapObjectActor(const TMap<UObject*, AActor*>& map, const FObjectActorPredicate& predicate)
{
	return copyIf(map, predicate);
}
#pragma endregion

#pragma region CopyIfMapActor
TMap<AActor*, bool> UUtilityLibrary::copyIfMapActorBoolean(const TMap<AActor*, bool>& map, const FActorBooleanPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<AActor*, int32> UUtilityLibrary::copyIfMapActorInteger(const TMap<AActor*, int32>& map, const FActorIntegerPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<AActor*, int64> UUtilityLibrary::copyIfMapActorInteger64(const TMap<AActor*, int64>& map, const FActorInteger64Predicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<AActor*, float> UUtilityLibrary::copyIfMapActorFloat(const TMap<AActor*, float>& map, const FActorFloatPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<AActor*, FString> UUtilityLibrary::copyIfMapActorString(const TMap<AActor*, FString>& map, const FActorStringPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<AActor*, FName> UUtilityLibrary::copyIfMapActorName(const TMap<AActor*, FName>& map, const FActorNamePredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<AActor*, FText> UUtilityLibrary::copyIfMapActorText(const TMap<AActor*, FText>& map, const FActorTextPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<AActor*, UObject*> UUtilityLibrary::copyIfMapActorObject(const TMap<AActor*, UObject*>& map, const FActorObjectPredicate& predicate)
{
	return copyIf(map, predicate);
}

TMap<AActor*, AActor*> UUtilityLibrary::copyIfMapActorActor(const TMap<AActor*, AActor*>& map, const FActorActorPredicate& predicate)
{
	return copyIf(map, predicate);
}

#pragma endregion
