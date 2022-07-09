// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "StateMachineActions/StateMachineAction.h"
#include "Utility/Utility.h"

template<typename... Args>
class LOSTCONNECTION_API StateMachine
{
private:
	TArray<TSharedPtr<StateMachineAction<Args...>>> actions;
	int32 activeIndex;

public:
	StateMachine();

	bool process(const Args&... args);

	/**
	* Add action to chain of actions.
	* If action returns true chain move to next action
	* @param condition Condition for run action
	* @param action Action to execute
	*/
	void addAction
	(
		TFunction<bool(const Args&...)>&& condition,
		TFunction<bool(const Args&...)>&& action
	);

	void addAction(const TSharedPtr<StateMachineAction<Args...>>& action);

	void addAction(TSharedPtr<StateMachineAction<Args...>>&& action);

	template<template<typename> typename AIActionT, typename... ConstructArgs>
	void addAction(ConstructArgs&&... args);

	void clear();

	void resetExecution();

	int32 size() const;

	bool isEmpty() const;

	bool isNotEmpty() const;

	bool isExecutionEnd() const;

	~StateMachine() = default;
};

template<typename... Args>
StateMachine<Args...>::StateMachine() :
	activeIndex(0)
{

}

template<typename... Args>
bool StateMachine<Args...>::process(const Args&... args)
{
	if (this->isEmpty())
	{
		UE_LOG(LogLostConnection, Error, TEXT("Actions not initialized %s %s"), __FILE__, __LINE__);

		return false;
	}

	TSharedPtr<StateMachineAction<Args...>>& currentAction = actions[activeIndex];

	if (currentAction->executeCondition(args...))
	{
		if (currentAction->executeAction(args...))
		{
			if (activeIndex != actions.Num() - 1)
			{
				activeIndex++;
			}
			else
			{
				activeIndex = 0;
			}

			return true;
		}

		return false;
	}

	return false;
}

template<typename... Args>
void StateMachine<Args...>::addAction(TFunction<bool(const Args&...)>&& condition, TFunction<bool(const Args&...)>&& action)
{
	actions.Add(MakeShared<StateMachineAction<Args...>>(MoveTemp(condition), MoveTemp(action)));
}

template<typename... Args>
void StateMachine<Args...>::addAction(const TSharedPtr<StateMachineAction<Args...>>& action)
{
	actions.Add(action);
}

template<typename... Args>
void StateMachine<Args...>::addAction(TSharedPtr<StateMachineAction<Args...>>&& action)
{
	actions.Add(MoveTemp(action));
}

template<typename... Args>
template<template<typename> typename AIActionT, typename... ConstructArgs>
void StateMachine<Args...>::addAction(ConstructArgs&&... args)
{
	actions.Add(MakeShared<AIActionT<Args...>>(Forward<ConstructArgs>(args)...));
}

template<typename... Args>
void StateMachine<Args...>::clear()
{
	actions.Empty();

	this->resetExecution();
}

template<typename... Args>
void StateMachine<Args...>::resetExecution()
{
	activeIndex = 0;
}

template<typename... Args>
int32 StateMachine<Args...>::size() const
{
	return actions.Num();
}

template<typename... Args>
bool StateMachine<Args...>::isEmpty() const
{
	return actions.IsEmpty();
}

template<typename... Args>
bool StateMachine<Args...>::isNotEmpty() const
{
	return !actions.IsEmpty();
}

template<typename... Args>
bool StateMachine<Args...>::isExecutionEnd() const
{
	return !activeIndex;
}
