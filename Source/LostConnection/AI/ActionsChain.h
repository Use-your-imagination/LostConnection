// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Utility/Utility.h"

template<typename... Args>
class LOSTCONNECTION_API ActionsChain
{
private:
	template<typename... FunctionArgs>
	struct Action
	{
		TFunction<bool(const FunctionArgs&...)> condition;
		TFunction<bool(const FunctionArgs&...)> action;
		TFunction<bool(bool)> processBehaviorTree;

		Action(TFunction<bool(const FunctionArgs&...)>&& condition, TFunction<bool(const FunctionArgs&...)>&& action, TFunction<bool(bool)>&& processBehaviorTree);
	};

private:
	TArray<Action<Args...>> actions;
	Action<Args...>* currentAction;

public:
	ActionsChain();

	bool process(const Args&... args);

	void addAction
	(
		TFunction<bool(const Args&...)>&& condition,
		TFunction<bool(const Args&...)>&& action,
		TFunction<bool(bool)>&& processBehaviorTree = [](bool isProcessingBehaviorTree) -> bool { return isProcessingBehaviorTree; }
	);

	void clear();

	void resetExecution();

	int32 size() const;

	bool isEmpty() const;

	bool isNotEmpty() const;

	bool isExecutionEnd() const;

	~ActionsChain() = default;
};

template<typename... Args>
template<typename... FunctionArgs>
ActionsChain<Args...>::Action<FunctionArgs...>::Action(TFunction<bool(const FunctionArgs&...)>&& condition, TFunction<bool(const FunctionArgs&...)>&& action, TFunction<bool(bool)>&& processBehaviorTree) :
	condition(MoveTemp(condition)),
	action(MoveTemp(action)),
	processBehaviorTree(MoveTemp(processBehaviorTree))
{

}

template<typename... Args>
ActionsChain<Args...>::ActionsChain() :
	currentAction(nullptr)
{

}

template<typename... Args>
bool ActionsChain<Args...>::process(const Args&... args)
{
	if (!currentAction && this->isNotEmpty())
	{
		currentAction = &actions[0];
	}
	else if (this->isEmpty())
	{
		UE_LOG(LogLostConnection, Error, TEXT("Actions not initialized %s %s"), __FILE__, __LINE__);

		return false;
	}

	if (currentAction->condition(args...))
	{
		bool result = currentAction->action(args...);
		const TFunction<bool(bool)>& processBehaviorTree = currentAction->processBehaviorTree;

		if (result)
		{
			if (currentAction != &actions.Last())
			{
				currentAction++;
			}
			else
			{
				currentAction = nullptr;
			}
		}
		
		return processBehaviorTree(result);
	}

	return false;
}

template<typename... Args>
void ActionsChain<Args...>::addAction(TFunction<bool(const Args&...)>&& condition, TFunction<bool(const Args&...)>&& action, TFunction<bool(bool)>&& processBehaviorTree)
{
	actions.Emplace(MoveTemp(condition), MoveTemp(action), MoveTemp(processBehaviorTree));
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
	currentAction = nullptr;
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
	return !StaticCast<bool>(currentAction);
}
