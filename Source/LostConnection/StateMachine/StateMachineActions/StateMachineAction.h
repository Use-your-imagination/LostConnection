// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

template<typename... Args>
class LOSTCONNECTION_API StateMachineAction
{
protected:
	TFunction<bool(const Args&...)> condition;
	TFunction<bool(const Args&...)> action;

public:
	StateMachineAction(TFunction<bool(const Args&...)>&& condition, TFunction<bool(const Args&...)>&& action);

	bool executeCondition(const Args&... args) const;

	bool executeAction(const Args&... args) const;

	const TFunction<bool(const Args&...)>& getCondition() const;

	const TFunction<bool(const Args&...)>& getAction() const;

	virtual ~StateMachineAction() = default;
};

template<typename... Args>
StateMachineAction<Args...>::StateMachineAction(TFunction<bool(const Args&...)>&& condition, TFunction<bool(const Args&...)>&& action) :
	condition(MoveTemp(condition)),
	action(MoveTemp(action))
{

}

template<typename... Args>
bool StateMachineAction<Args...>::executeCondition(const Args&... args) const
{
	return condition(args...);
}

template<typename... Args>
bool StateMachineAction<Args...>::executeAction(const Args&... args) const
{
	return action(args...);
}

template<typename... Args>
const TFunction<bool(const Args&...)>& StateMachineAction<Args...>::getCondition() const
{
	return condition;
}

template<typename... Args>
const TFunction<bool(const Args&...)>& StateMachineAction<Args...>::getAction() const
{
	return action;
}
