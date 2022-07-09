// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "StateMachineAction.h"

template<typename... Args>
class LOSTCONNECTION_API WaitAction : public StateMachineAction<Args...>
{
private:
	double waitSeconds;
	double currentTime;

public:
	WaitAction(double secondsToWait);

	~WaitAction() = default;
};

template<typename... Args>
WaitAction<Args...>::WaitAction(double secondsToWait) :
	StateMachineAction
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
		}
	),
	waitSeconds(secondsToWait),
	currentTime(secondsToWait)
{

}
