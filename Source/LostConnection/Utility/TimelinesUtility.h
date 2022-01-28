// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "Components/TimelineComponent.h"

#include "TimelinesUtility.generated.h"

UCLASS()
class LOSTCONNECTION_API UTimelinesUtility : public UObject
{
	GENERATED_BODY()

private:
	TArray<FTimeline> timelines;

public:
	UTimelinesUtility() = default;

	void Tick(float DeltaTime);

	UFUNCTION(Category = Timelines, BlueprintCallable, Meta = (AutoCreateRefTerm = "finishCallback"))
	void initAndStartTimeline(UCurveFloat* curve, const FOnTimelineFloat& function, const FOnTimelineEvent& finishCallback, float curveDuration = 5.0f);

	~UTimelinesUtility() = default;
};
