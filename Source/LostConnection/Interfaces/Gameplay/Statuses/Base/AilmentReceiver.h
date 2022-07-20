// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "NiagaraComponent.h"

#include "StatusReceiver.h"

#include "AilmentReceiver.generated.h"

UINTERFACE()
class UAilmentReceiver : public UStatusReceiver
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IAilmentReceiver : public IStatusReceiver
{
	GENERATED_BODY()

public:
	IAilmentReceiver() = default;

	virtual void applySwarmAilment(const TObjectPtr<class USwarmAilment>& swarm) = 0;
};
