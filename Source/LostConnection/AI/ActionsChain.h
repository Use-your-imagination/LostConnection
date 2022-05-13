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

		Action(TFunction<bool(const FunctionArgs&...)>&& condition, TFunction<bool(const FunctionArgs&...)>&& action);
	};

private:
	TArray<Action<Args...>> actions;
	Action<Args...>* currentAction;

public:
	ActionsChain();

	bool process(const Args&... args);

	void addAction(TFunction<bool(const Args&...)>&& condition, TFunction<bool(const Args&...)>&& action);

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
ActionsChain<Args...>::Action<FunctionArgs...>::Action(TFunction<bool(const FunctionArgs&...)>&& condition, TFunction<bool(const FunctionArgs&...)>&& action) :
	condition(MoveTemp(condition)),
	action(MoveTemp(action))
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
		
		return result;
	}

	return false;
}

template<typename... Args>
void ActionsChain<Args...>::addAction(TFunction<bool(const Args&...)>&& condition, TFunction<bool(const Args&...)>&& action)
{
	actions.Emplace(MoveTemp(condition), MoveTemp(action));
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
