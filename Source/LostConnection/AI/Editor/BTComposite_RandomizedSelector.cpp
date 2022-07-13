// Copyright (c) 2022 Use Your Imagination

#include "BTComposite_RandomizedSelector.h"

#include "LostConnectionStyle.h"
#include "Utility/Utility.h"

UBTComposite_RandomizedSelector::UBTComposite_RandomizedSelector()
{
	NodeName = "Randomized Selector";
}

int32 UBTComposite_RandomizedSelector::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	if (PrevChild == BTSpecialChild::NotInitialized)
	{
#if UE_BUILD_DEVELOPMENT
		if (executionChances.Num() < GetChildrenNum())
		{
			UE_LOG(LogLostConnection, Fatal, TEXT("Randomized Selector's Execution Chances array elements < nodes"));
		}
#endif // UE_BUILD_DEVELOPMENT

		realExecutionChances.Init(0, executionChances.Num());

		for (int32 i = 0; i < GetChildrenNum(); i++)
		{
			for (int32 j = 0; j <= i; j++)
			{
				realExecutionChances[i] += executionChances[j];
			}
		}

#if UE_BUILD_DEVELOPMENT
		if (Algo::AnyOf(realExecutionChances, [](float chance) { return chance > 100.0f; }))
		{
			UE_LOG(LogLostConnection, Warning, TEXT("Last node has chance > 100%%"));
		}
		else if (realExecutionChances.Last() < 100.0f)
		{
			UE_LOG(LogLostConnection, Error, TEXT("Last node has chance < 100%%"));
		}
#endif // UE_BUILD_DEVELOPMENT

		for (int32 i = 0; i < GetChildrenNum(); i++)
		{
			if (Utility::checkChanceProc(realExecutionChances[i]))
			{
				return i;
			}
		}
	}

	if (LastResult == EBTNodeResult::Type::Succeeded)
	{
		return BTSpecialChild::ReturnToParent;
	}

	for (int32 i = PrevChild; i < GetChildrenNum(); i++)
	{
		if (Utility::checkChanceProc(realExecutionChances[i]))
		{
			return i;
		}
	}

	return BTSpecialChild::ReturnToParent;
}

#if WITH_EDITOR
FName UBTComposite_RandomizedSelector::GetNodeIconName() const
{
	FLostConnectionStyle::get();

	return FName("LostConnectionStyle.Editor.AI.RandomizedSelector.Icon");
}
#endif
