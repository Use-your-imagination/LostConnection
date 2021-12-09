// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "NiagaraComponent.h"

#include "StatusReceiver.h"

#include "AilmentReceiver.generated.h"

UINTERFACE(MinimalAPI)
class UAilmentReceiver : public UStatusReceiver
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IAilmentReceiver : public IStatusReceiver
{
	GENERATED_BODY()

public:
	IAilmentReceiver() = default;

	virtual void applySwarmAilment(class USwarmAilment* swarm) = 0;
};
