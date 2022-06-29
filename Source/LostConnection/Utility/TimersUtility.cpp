// Copyright (c) 2021 Use Your Imagination

#include "TimersUtility.h"

#include "Async/ParallelFor.h"
#include "Algo/ForEach.h"
#include "Algo/RemoveIf.h"

#pragma warning(disable: 4458)

timerData::timerData(const TFunction<void()>& timer, float rate, bool loop, float firstDelay) :
	timer(timer),
	rate(rate),
	loop(loop),
	firstDelay(firstDelay),
	currentTime(0.0f)
{

}

void TimersUtility::addTimer(const TFunction<void()>& function, float rate, bool loop, float firstDelay)
{
	timers.Emplace(function, rate, loop, firstDelay);
}

void TimersUtility::removeTimer(int32 index)
{
	timers.RemoveAt(index);
}

int32 TimersUtility::size() const
{
	return timers.Num();
}

void TimersUtility::processTimers(float DeltaSeconds)
{
	TArray<timerData*> timersToInvoke;
	auto body = [this, &DeltaSeconds, &timersToInvoke](int32 index)
	{
		timerData& timer = timers[index];

		bool isInvoke = false;

		if (timer.firstDelay > 0.0f)
		{
			timer.firstDelay -= DeltaSeconds;

			if (timer.firstDelay <= 0.0f)
			{
				timer.currentTime += FMath::Abs(timer.firstDelay);

				timer.firstDelay = 0.0f;

				isInvoke = true;
			}
		}
		else
		{
			timer.currentTime += DeltaSeconds;

			if (timer.currentTime >= timer.rate)
			{
				timer.currentTime -= timer.rate;

				isInvoke = true;
			}
		}

		if (isInvoke)
		{
			timersToInvoke[index] = &timer;
		}
	};

	timersToInvoke.Init(nullptr, timers.Num());

	ParallelFor(timers.Num(), body, EParallelForFlags::Unbalanced);

	Algo::ForEachIf
	(
		timersToInvoke,
		[](timerData* timer) { return StaticCast<bool>(timer); },
		[](timerData* timer) { timer->timer(); }
	);

	for (int32 i = 0; i < timersToInvoke.Num(); i++)
	{
		if ((timersToInvoke[i] && !timersToInvoke[i]->loop) && (timersToInvoke[i] == &timers[i]))
		{
			timers.RemoveAt(i);
			timersToInvoke.RemoveAt(i);

			i--;
		}
	}
}

const timerData& TimersUtility::operator[](int32 index) const
{
	return timers[index];
}
