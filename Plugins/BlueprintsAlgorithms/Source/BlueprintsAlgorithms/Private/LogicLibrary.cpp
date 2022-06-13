// Copyright (c) 2022 Arkadiy Zakharov

#include "LogicLibrary.h"

#include "Algo/AllOf.h"
#include "Algo/AnyOf.h"

template<typename T, typename PredicateT>
static bool allOf(const T& values, const PredicateT& predicate)
{
	if (!predicate.IsBound())
	{
		return false;
	}

	return Algo::AllOf(values, [&predicate](const auto& value) { return predicate.Execute(value); });
}

template<typename T, typename PredicateT>
static bool anyOf(const T& values, const PredicateT& predicate)
{
	if (!predicate.IsBound())
	{
		return false;
	}

	return Algo::AnyOf(values, [&predicate](const auto& value) { return predicate.Execute(value); });
}

static bool defaultAllOfBool(const TArray<bool>& values)
{
	static TDelegate<bool(bool)> predicate;

	if (!predicate.IsBound())
	{
		predicate.BindLambda([](bool value)
			{
				return value;
			});
	}

	return allOf(values, predicate);
}

static bool defaultAnyOfBoolean(const TArray<bool>& values)
{
	static TDelegate<bool(bool)> predicate;

	if (!predicate.IsBound())
	{
		predicate.BindLambda([](bool value)
			{
				return value;
			});
	}

	return anyOf(values, predicate);
}

bool ULogicLibrary::allOfBooleanArray(const TArray<bool>& values, const FBooleanPredicate& predicate)
{
	if (!predicate.IsBound())
	{
		return defaultAllOfBool(values);
	}

	return allOf(values, predicate);
}

bool ULogicLibrary::allOfIntegerArray(const TArray<int32>& values, const FIntegerPredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfIntegerSet(const TSet<int32>& values, const FIntegerPredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfInteger64Array(const TArray<int64>& values, const FInteger64Predicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfInteger64Set(const TSet<int64>& values, const FInteger64Predicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfFloatArray(const TArray<float>& values, const FFloatPredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfFloatSet(const TSet<float>& values, const FFloatPredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfStringArray(const TArray<FString>& values, const FStringPredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfStringSet(const TSet<FString>& values, const FStringPredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfNameArray(const TArray<FName>& values, const FNamePredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfNameSet(const TSet<FName>& values, const FNamePredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfTextArray(const TArray<FText>& values, const FTextPredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfObjectArray(const TArray<UObject*>& values, const FObjectPredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfObjectSet(const TSet<UObject*>& values, const FObjectPredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfActorArray(const TArray<AActor*>& values, const FActorPredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::allOfActorSet(const TSet<AActor*>& values, const FActorPredicate& predicate)
{
	return allOf(values, predicate);
}

bool ULogicLibrary::anyOfBooleanArray(const TArray<bool>& values, const FBooleanPredicate& predicate)
{
	if (!predicate.IsBound())
	{
		return defaultAnyOfBoolean(values);
	}

	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfIntegerArray(const TArray<int32>& values, const FIntegerPredicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfIntegerSet(const TSet<int32>& values, const FIntegerPredicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfInteger64Array(const TArray<int64>& values, const FInteger64Predicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfInteger64Set(const TSet<int64>& values, const FInteger64Predicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfFloatArray(const TArray<float>& values, const FFloatPredicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfFloatSet(const TSet<float>& values, const FFloatPredicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfStringArray(const TArray<FString>& values, const FStringPredicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfStringSet(const TSet<FString>& values, const FStringPredicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfNameArray(const TArray<FName>& values, const FNamePredicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfNameSet(const TSet<FName>& values, const FNamePredicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfTextArray(const TArray<FText>& values, const FTextPredicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfObjectArray(const TArray<UObject*>& values, const FObjectPredicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfObjectSet(const TSet<UObject*>& values, const FObjectPredicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfActorArray(const TArray<AActor*>& values, const FActorPredicate& predicate)
{
	return anyOf(values, predicate);
}

bool ULogicLibrary::anyOfActorSet(const TSet<AActor*>& values, const FActorPredicate& predicate)
{
	return anyOf(values, predicate);
}
