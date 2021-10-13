#include "TimersUtility.h"

#pragma warning(disable: 4458)

UTimersUtility::UTimersUtility() :
	world(nullptr)
{

}

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

void UTimersUtility::clear()
{
	if (world && world->IsValidLowLevel())
	{
		FTimerManager* manager = &world->GetTimerManager();

		if (manager)
		{
			for (auto& timer : timers)
			{
				manager->ClearTimer(timer);
			}

			timers.Empty();
		}
	}
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

UTimersUtility::~UTimersUtility()
{
	if (IsValidLowLevel())
	{
		this->clear();
	}
}
