// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/StreamableManager.h"

#include "LatentActions.h"

class LOSTCONNECTION_API FLoadAssetsDelayAction : public FPendingLatentAction
{
private:
	TSharedPtr<FStreamableHandle> handle;
	FName executionFunction;
	int32 outputLink;
	FWeakObjectPtr callbackTarget;

public:
	FLoadAssetsDelayAction(const TSharedPtr<FStreamableHandle>& handle, const FLatentActionInfo& info);

	void UpdateOperation(FLatentResponse& response) override;

	~FLoadAssetsDelayAction() = default;
};
