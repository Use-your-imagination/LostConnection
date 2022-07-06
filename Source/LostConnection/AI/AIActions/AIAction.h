// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

template<typename... Args>
class LOSTCONNECTION_API AIAction
{
protected:
	TFunction<bool(const Args&...)> condition;
	TFunction<bool(const Args&...)> action;
	TFunction<bool(bool)> processBehaviorTree;

public:
	AIAction(TFunction<bool(const Args&...)>&& condition, TFunction<bool(const Args&...)>&& action, TFunction<bool(bool)>&& processBehaviorTree);

	bool executeCondition(const Args&... args) const;

	bool executeAction(const Args&... args) const;

	bool executeProcessBehaviorTree(bool isProcessingBehaviorTree) const;

	const TFunction<bool(const Args&...)>& getCondition() const;

	const TFunction<bool(const Args&...)>& getAction() const;

	const TFunction<bool(bool)>& getProcessBehaviorTree() const;

	virtual ~AIAction() = default;
};

template<typename... Args>
AIAction<Args...>::AIAction(TFunction<bool(const Args&...)>&& condition, TFunction<bool(const Args&...)>&& action, TFunction<bool(bool)>&& processBehaviorTree) :
	condition(MoveTemp(condition)),
	action(MoveTemp(action)),
	processBehaviorTree(MoveTemp(processBehaviorTree))
{

}

template<typename... Args>
bool AIAction<Args...>::executeCondition(const Args&... args) const
{
	return condition(args...);
}

template<typename... Args>
bool AIAction<Args...>::executeAction(const Args&... args) const
{
	return action(args...);
}

template<typename... Args>
bool AIAction<Args...>::executeProcessBehaviorTree(bool isProcessingBehaviorTree) const
{
	return processBehaviorTree(isProcessingBehaviorTree);
}

template<typename... Args>
const TFunction<bool(const Args&...)>& AIAction<Args...>::getCondition() const
{
	return condition;
}

template<typename... Args>
const TFunction<bool(const Args&...)>& AIAction<Args...>::getAction() const
{
	return action;
}

template<typename... Args>
const TFunction<bool(bool)>& AIAction<Args...>::getProcessBehaviorTree() const
{
	return processBehaviorTree;
}
