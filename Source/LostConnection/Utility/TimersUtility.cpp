#include "TimersUtility.h"

#pragma warning(disable: 4458)

void UTimersUtility::addTimer(const TFunction<void()>& function, float rate, bool loop, float firstDelay)
{
	FTimerDelegate delegate;

	delegate.BindLambda(function);

	timers.Emplace();

	world->GetTimerManager().SetTimer(timers.Last(), delegate, rate, loop, firstDelay);
}

void UTimersUtility::removeTimer(size_t index)
{
	timers.RemoveAt(index);
}

size_t UTimersUtility::size() const
{
	return timers.Num();
}

void UTimersUtility::setWorld(UWorld* world)
{
	this->world = world;
}

const FTimerHandle& UTimersUtility::operator[](size_t index) const
{
	return timers[index];
}

FTimerHandle& UTimersUtility::operator [] (size_t index)
{
	return timers[index];
}