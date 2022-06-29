// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

struct LOSTCONNECTION_API timerData
{
	TFunction<void()> timer;
	float rate;
	bool loop;
	float firstDelay;
	float currentTime;

public:
	timerData(const TFunction<void()>& timer, float rate, bool loop = true, float firstDelay = 0.0f);

	~timerData() = default;
};

class LOSTCONNECTION_API TimersUtility
{
private:
	TArray<timerData> timers;

public:
	TimersUtility() = default;

	void addTimer(const TFunction<void()>& function, float rate, bool loop = true, float firstDelay = 0.0f);

	void removeTimer(int32 index);

	int32 size() const;

	void processTimers(float DeltaSeconds);

	const timerData& operator [] (int32 index) const;

	~TimersUtility() = default;
};
