// Copyright (c) 2021 Use-your-imagination

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

	void removeTimer(const timerData& timer);

	int32 size() const;

	void processTimers(float DeltaTime);

	const timerData& operator [] (int32 index) const;

	~TimersUtility() = default;
};
