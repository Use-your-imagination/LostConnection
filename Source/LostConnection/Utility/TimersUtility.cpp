// Copyright (c) 2021 Use-your-imagination

#include "TimersUtility.h"

#include "Async/ParallelFor.h"
#include "Algo/ForEach.h"

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

void TimersUtility::processTimers(float DeltaTime)
{
	TArray<TFunction<void()>*> timersToInvoke;
	auto body = [this, &DeltaTime, &timersToInvoke](int32 index)
	{
		timerData& timer = timers[index];

		bool isInvoke = false;

		if (timer.firstDelay > 0.0f)
		{
			timer.firstDelay -= DeltaTime;

			if (timer.firstDelay <= 0.0f)
			{
				timer.currentTime += FMath::Abs(timer.firstDelay);

				timer.firstDelay = 0.0f;

				isInvoke = true;
			}
		}
		else
		{
			timer.currentTime += DeltaTime;

			if (timer.currentTime >= timer.rate)
			{
				timer.currentTime -= timer.rate;

				isInvoke = true;
			}
		}

		if (isInvoke)
		{
			timersToInvoke[index] = &timer.timer;
		}
	};

	timersToInvoke.Init(nullptr, timers.Num());

	ParallelFor(timers.Num(), body, EParallelForFlags::Unbalanced);

	Algo::ForEachIf
	(
		timersToInvoke,
		[](TFunction<void()>* timer) { return StaticCast<bool>(timer); },
		[](TFunction<void()>* timer) { (*timer)(); }
	);
}

const timerData& TimersUtility::operator[](int32 index) const
{
	return timers[index];
}
