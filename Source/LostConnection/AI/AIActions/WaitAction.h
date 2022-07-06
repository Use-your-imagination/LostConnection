// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "AIAction.h"

template<typename... Args>
class LOSTCONNECTION_API WaitAction : public AIAction<Args...>
{
private:
	double waitSeconds;
	double currentTime;
	bool resetState;

public:
	/**
	* @param resetState Value that returns to start in behavior tree
	*/
	WaitAction(double secondsToWait, bool resetState = true);

	~WaitAction() = default;
};

template<typename... Args>
WaitAction<Args...>::WaitAction(double secondsToWait, bool resetState) :
	AIAction
	(
		[](const Args&...) -> bool
		{
			return true;
		},
		[this](const Args&...) -> bool
		{
			if (currentTime)
			{
				currentTime = FMath::Max(0.0, currentTime - FApp::GetDeltaTime());
			}
			else
			{
				currentTime = waitSeconds;
			}

			return !StaticCast<bool>(currentTime);
		},
		[this](bool) { return this->resetState; }
	),
	waitSeconds(secondsToWait),
	currentTime(secondsToWait),
	resetState(resetState)
{

}
