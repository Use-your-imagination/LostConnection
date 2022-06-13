// Copyright (c) 2022 Arkadiy Zakharov

#include "SortingLibrary.h"

#include "Algo/Sort.h"
#include "Algo/IsSorted.h"

template<typename T, typename PredicateT>
static TArray<T>& sortArray(TArray<T>& arrayReference, const PredicateT& predicate, ESortingType& type)
{
	if (predicate.IsBound())
	{
		Algo::Sort(arrayReference, [&predicate](const T& first, const T& second) { return predicate.Execute(first, second); });

		type = ESortingType::byPredicate;
	}
	else
	{
		Algo::Sort(arrayReference);

		type = ESortingType::standard;
	}

	return arrayReference;
}

template<typename T, typename PredicateT>
static bool isSortedArray(const TArray<T>& array, const PredicateT& predicate, ESortingType& type)
{
	if (predicate.IsBound())
	{
		type = ESortingType::byPredicate;

		return Algo::IsSorted(array, [&predicate](const T& first, const T& second) { return predicate.Execute(first, second); });
	}
	else
	{
		type = ESortingType::standard;

		return Algo::IsSorted(array);
	}
}

TArray<int32>& USortingLibrary::sortByReferenceIntegerArray(TArray<int32>& arrayReference, const FIntegerSortPredicate& predicate, ESortingType& type)
{
	return sortArray(arrayReference, predicate, type);
}

TArray<int64>& USortingLibrary::sortByReferenceInteger64Array(TArray<int64>& arrayReference, const FInteger64SortPredicate& predicate, ESortingType& type)
{
	return sortArray(arrayReference, predicate, type);
}

TArray<float>& USortingLibrary::sortByReferenceFloatArray(TArray<float>& arrayReference, const FFloatSortPredicate& predicate, ESortingType& type)
{
	return sortArray(arrayReference, predicate, type);
}

TArray<FString>& USortingLibrary::sortByReferenceStringArray(TArray<FString>& arrayReference, const FStringSortPredicate& predicate, ESortingType& type)
{
	return sortArray(arrayReference, predicate, type);
}

TArray<FName>& USortingLibrary::sortByReferenceNameArray(TArray<FName>& arrayReference, const FNameSortPredicate& predicate)
{
	Algo::Sort(arrayReference, [&predicate](const FName& first, const FName& second) { return predicate.Execute(first, second); });

	return arrayReference;
}

TArray<FText>& USortingLibrary::sortByReferenceTextArray(TArray<FText>& arrayReference, const FTextSortPredicate& predicate)
{
	Algo::Sort(arrayReference, [&predicate](const FText& first, const FText& second) { return predicate.Execute(first, second); });

	return arrayReference;
}

TArray<UObject*>& USortingLibrary::sortByReferenceObjectArray(TArray<UObject*>& arrayReference, const FObjectSortPredicate& predicate)
{
	ESortingType type;

	return sortArray(arrayReference, predicate, type);
}

TArray<AActor*>& USortingLibrary::sortByReferenceActorArray(TArray<AActor*>& arrayReference, const FActorSortPredicate& predicate)
{
	ESortingType type;

	return sortArray(arrayReference, predicate, type);
}

TArray<int32> USortingLibrary::sortIntegerArray(const TArray<int32>& array, const FIntegerSortPredicate& predicate, ESortingType& type)
{
	TArray<int32> tem = array;

	sortArray(tem, predicate, type);

	return tem;
}

TArray<int64> USortingLibrary::sortInteger64Array(const TArray<int64>& array, const FInteger64SortPredicate& predicate, ESortingType& type)
{
	TArray<int64> tem = array;

	sortArray(tem, predicate, type);

	return tem;
}

TArray<float> USortingLibrary::sortFloatArray(const TArray<float>& array, const FFloatSortPredicate& predicate, ESortingType& type)
{
	TArray<float> tem = array;

	sortArray(tem, predicate, type);

	return tem;
}

TArray<FString> USortingLibrary::sortStringArray(const TArray<FString>& array, const FStringSortPredicate& predicate, ESortingType& type)
{
	TArray<FString> tem = array;

	sortArray(tem, predicate, type);

	return tem;
}

TArray<FName> USortingLibrary::sortNameArray(const TArray<FName>& array, const FNameSortPredicate& predicate)
{
	TArray<FName> tem = array;

	Algo::Sort(tem, [&predicate](const FName& first, const FName& second) { return predicate.Execute(first, second); });

	return tem;
}

TArray<FText> USortingLibrary::sortTextArray(const TArray<FText>& array, const FTextSortPredicate& predicate)
{
	TArray<FText> tem = array;

	Algo::Sort(tem, [&predicate](const FText& first, const FText& second) { return predicate.Execute(first, second); });

	return tem;
}

TArray<UObject*> USortingLibrary::sortObjectArray(const TArray<UObject*>& array, const FObjectSortPredicate& predicate)
{
	TArray<UObject*> tem = array;
	ESortingType type;

	sortArray(tem, predicate, type);

	return tem;
}

TArray<AActor*> USortingLibrary::sortActorArray(const TArray<AActor*>& array, const FActorSortPredicate& predicate)
{
	TArray<AActor*> tem = array;
	ESortingType type;

	sortArray(tem, predicate, type);

	return tem;
}

bool USortingLibrary::isSortedIntegerArray(const TArray<int32>& array, const FIntegerSortPredicate& predicate, ESortingType& type)
{
	return isSortedArray(array, predicate, type);
}

bool USortingLibrary::isSortedInteger64Array(const TArray<int64>& array, const FInteger64SortPredicate& predicate, ESortingType& type)
{
	return isSortedArray(array, predicate, type);
}

bool USortingLibrary::isSortedFloatArray(const TArray<float>& array, const FFloatSortPredicate& predicate, ESortingType& type)
{
	return isSortedArray(array, predicate, type);
}

bool USortingLibrary::isSortedStringArray(const TArray<FString>& array, const FStringSortPredicate& predicate, ESortingType& type)
{
	return isSortedArray(array, predicate, type);
}

bool USortingLibrary::isSortedNameArray(const TArray<FName>& array, const FNameSortPredicate& predicate)
{
	return Algo::IsSorted(array, [&predicate](const FName& first, const FName& second) { return predicate.Execute(first, second); });
}

bool USortingLibrary::isSortedTextArray(const TArray<FText>& array, const FTextSortPredicate& predicate)
{
	return Algo::IsSorted(array, [&predicate](const FText& first, const FText& second) { return predicate.Execute(first, second); });
}

bool USortingLibrary::isSortedObjectArray(const TArray<UObject*>& array, const FObjectSortPredicate& predicate)
{
	ESortingType type;

	return isSortedArray(array, predicate, type);
}

bool USortingLibrary::isSortedActorArray(const TArray<AActor*>& array, const FActorSortPredicate& predicate)
{
	ESortingType type;

	return isSortedArray(array, predicate, type);
}
