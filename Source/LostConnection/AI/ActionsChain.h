// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "AIActions/AIAction.h"
#include "Utility/Utility.h"

template<typename... Args>
class LOSTCONNECTION_API ActionsChain
{
private:
	TArray<TSharedPtr<AIAction<Args...>>> actions;
	int32 activeIndex;

public:
	ActionsChain();

	bool process(const Args&... args);

	/**
	* Add action to chain of actions.
	* If action returns true chain move to next action
	* @param condition Condition for run action
	* @param action Action to execute
	* @param processBehaviorTree For Selector true means return to start, for sequence true means execute next AI node
	*/
	void addAction
	(
		TFunction<bool(const Args&...)>&& condition,
		TFunction<bool(const Args&...)>&& action,
		TFunction<bool(bool)>&& processBehaviorTree = [](bool isProcessingBehaviorTree) -> bool { return isProcessingBehaviorTree; }
	);

	void addAction(const TSharedPtr<AIAction<Args...>>& action);

	void addAction(TSharedPtr<AIAction<Args...>>&& action);

	template<template<typename> typename AIActionT, typename... ConstructArgs>
	void addAction(ConstructArgs&&... args);

	void clear();

	void resetExecution();

	int32 size() const;

	bool isEmpty() const;

	bool isNotEmpty() const;

	bool isExecutionEnd() const;

	~ActionsChain() = default;
};

template<typename... Args>
ActionsChain<Args...>::ActionsChain() :
	activeIndex(0)
{

}

template<typename... Args>
bool ActionsChain<Args...>::process(const Args&... args)
{
	if (this->isEmpty())
	{
		UE_LOG(LogLostConnection, Error, TEXT("Actions not initialized %s %s"), __FILE__, __LINE__);

		return false;
	}

	TSharedPtr<AIAction<Args...>>& currentAction = actions[activeIndex];

	if (currentAction->executeCondition(args...))
	{
		bool result = currentAction->executeAction(args...);
		const TFunction<bool(bool)>& processBehaviorTree = currentAction->getProcessBehaviorTree();

		if (result)
		{
			if (activeIndex != actions.Num() - 1)
			{
				activeIndex++;
			}
			else
			{
				activeIndex = 0;
			}
		}

		return processBehaviorTree(result);
	}

	return false;
}

template<typename... Args>
void ActionsChain<Args...>::addAction(TFunction<bool(const Args&...)>&& condition, TFunction<bool(const Args&...)>&& action, TFunction<bool(bool)>&& processBehaviorTree)
{
	actions.Add(MakeShared<AIAction<Args...>>(MoveTemp(condition), MoveTemp(action), MoveTemp(processBehaviorTree)));
}

template<typename... Args>
void ActionsChain<Args...>::addAction(const TSharedPtr<AIAction<Args...>>& action)
{
	actions.Add(action);
}

template<typename... Args>
void ActionsChain<Args...>::addAction(TSharedPtr<AIAction<Args...>>&& action)
{
	actions.Add(MoveTemp(action));
}

template<typename... Args>
template<template<typename> typename AIActionT, typename... ConstructArgs>
void ActionsChain<Args...>::addAction(ConstructArgs&&... args)
{
	actions.Add(MakeShared<AIActionT<Args...>>(Forward<ConstructArgs>(args)...));
}

template<typename... Args>
void ActionsChain<Args...>::clear()
{
	actions.Empty();

	this->resetExecution();
}

template<typename... Args>
void ActionsChain<Args...>::resetExecution()
{
	activeIndex = 0;
}

template<typename... Args>
int32 ActionsChain<Args...>::size() const
{
	return actions.Num();
}

template<typename... Args>
bool ActionsChain<Args...>::isEmpty() const
{
	return actions.IsEmpty();
}

template<typename... Args>
bool ActionsChain<Args...>::isNotEmpty() const
{
	return !actions.IsEmpty();
}

template<typename... Args>
bool ActionsChain<Args...>::isExecutionEnd() const
{
	return !activeIndex;
}
