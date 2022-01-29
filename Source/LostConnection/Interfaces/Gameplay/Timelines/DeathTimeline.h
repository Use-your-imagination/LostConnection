// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "DeathTimeline.generated.h"

UINTERFACE(BlueprintType)
class UDeathTimeline : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDeathTimeline
{
	GENERATED_BODY()

public:
	IDeathTimeline() = default;

	virtual void deathTimelineUpdate(float value) = 0;

	virtual void deathTimelineFinished() = 0;
};
