// Copyright (c) 2022 Use Your Imagination

#include "TimelinesUtility.h"

void UTimelinesUtility::Tick(float DeltaTime)
{
	for (FTimeline& timeline : timelines)
	{
		timeline.TickTimeline(DeltaTime);
	}
}

void UTimelinesUtility::initAndStartTimeline(UCurveFloat* curve, const FOnTimelineFloat& function, const FOnTimelineEvent& finishCallback, float curveDuration)
{
	FTimeline* timeline = timelines.FindByPredicate([](const FTimeline& timeline) { return !timeline.IsPlaying(); });
	
	if (timeline)
	{
		*timeline = FTimeline();
	}
	else
	{
		timeline = &timelines.Emplace_GetRef();
	}

	timeline->AddInterpFloat(curve, function);

	timeline->SetTimelineLength(curveDuration);

	timeline->SetTimelineFinishedFunc(finishCallback);

	timeline->PlayFromStart();
}
