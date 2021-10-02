#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "TimersUtility.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API UTimersUtility : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<FTimerHandle> timers;

	UWorld* world;

public:
	UTimersUtility() = default;

	void addTimer(const TFunction<void()>& function, float rate, bool loop = true, float firstDelay = 0.0f);

	void removeTimer(size_t index);

	size_t size() const;

	void clear();

	void setWorld(UWorld* world);

	const FTimerHandle& operator [] (size_t index) const;

	FTimerHandle& operator [] (size_t index);

	~UTimersUtility();
};
