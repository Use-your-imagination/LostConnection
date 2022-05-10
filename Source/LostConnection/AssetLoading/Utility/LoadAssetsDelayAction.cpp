// Copyright (c) 2021 Use Your Imagination

#include "LoadAssetsDelayAction.h"

FLoadAssetsDelayAction::FLoadAssetsDelayAction(const TSharedPtr<FStreamableHandle>& handle, const FLatentActionInfo& info) :
	handle(handle),
	executionFunction(info.ExecutionFunction),
	outputLink(info.Linkage),
	callbackTarget(info.CallbackTarget)
{
	
}

void FLoadAssetsDelayAction::UpdateOperation(FLatentResponse& response)
{
	response.FinishAndTriggerIf(handle->HasLoadCompleted(), executionFunction, outputLink, callbackTarget);
}
