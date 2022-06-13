// Copyright (c) 2022 Arkadiy Zakharov

#include "OperatorsLibrary.h"

template<typename T, typename PredicateT>
static void compareByPredicate(const T& left, const T& right, const PredicateT& predicate, EThreeWayComparisonOperator& out)
{
	int32 result = predicate.Execute(left, right);

	if (result == -1)
	{
		out = EThreeWayComparisonOperator::less;
	}
	else if (result == 0)
	{
		out = EThreeWayComparisonOperator::equal;
	}
	else if (result == 1)
	{
		out = EThreeWayComparisonOperator::greater;
	}
}

void UOperatorsLibrary::intToInt(int32 left, int32 right, EThreeWayComparisonOperator& out)
{
	if (left < right)
	{
		out = EThreeWayComparisonOperator::less;
	}
	else if (left == right)
	{
		out = EThreeWayComparisonOperator::equal;
	}
	else
	{
		out = EThreeWayComparisonOperator::greater;
	}
}

void UOperatorsLibrary::intToInt64(int32 left, int64 right, EThreeWayComparisonOperator& out)
{
	if (StaticCast<int64>(left) < right)
	{
		out = EThreeWayComparisonOperator::less;
	}
	else if (StaticCast<int64>(left) == right)
	{
		out = EThreeWayComparisonOperator::equal;
	}
	else
	{
		out = EThreeWayComparisonOperator::greater;
	}
}

void UOperatorsLibrary::intToFloat(int32 left, float right, EThreeWayComparisonOperator& out)
{
	if (left < right)
	{
		out = EThreeWayComparisonOperator::less;
	}
	else if (left == right)
	{
		out = EThreeWayComparisonOperator::equal;
	}
	else
	{
		out = EThreeWayComparisonOperator::greater;
	}
}

void UOperatorsLibrary::int64ToInt64(int64 left, int64 right, EThreeWayComparisonOperator& out)
{
	if (left < right)
	{
		out = EThreeWayComparisonOperator::less;
	}
	else if (left == right)
	{
		out = EThreeWayComparisonOperator::equal;
	}
	else
	{
		out = EThreeWayComparisonOperator::greater;
	}
}

void UOperatorsLibrary::int64ToFloat(int64 left, float right, EThreeWayComparisonOperator& out)
{
	if (left < StaticCast<double>(right))
	{
		out = EThreeWayComparisonOperator::less;
	}
	else if (left == StaticCast<double>(right))
	{
		out = EThreeWayComparisonOperator::equal;
	}
	else
	{
		out = EThreeWayComparisonOperator::greater;
	}
}

void UOperatorsLibrary::floatToFloat(float left, float right, EThreeWayComparisonOperator& out)
{
	if (left < right)
	{
		out = EThreeWayComparisonOperator::less;
	}
	else if (left == right)
	{
		out = EThreeWayComparisonOperator::equal;
	}
	else
	{
		out = EThreeWayComparisonOperator::greater;
	}
}

void UOperatorsLibrary::objectToObject(const UObject* left, const UObject* right, const FObjectsThreeWayComparison& predicate, EThreeWayComparisonOperator& out)
{
	compareByPredicate(left, right, predicate, out);
}

void UOperatorsLibrary::actorToActor(const AActor* left, const AActor* right, const FActorsThreeWayComparison& predicate, EThreeWayComparisonOperator& out)
{
	compareByPredicate(left, right, predicate, out);
}
