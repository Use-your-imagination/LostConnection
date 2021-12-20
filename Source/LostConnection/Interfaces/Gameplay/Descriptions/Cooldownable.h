// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Cooldownable.generated.h"

UINTERFACE(BlueprintType)
class UCooldownable : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ICooldownable
{
	GENERATED_BODY()

public:
	ICooldownable() = default;

	virtual void startCooldown();

	virtual void processCooldown(float DeltaTime);

	virtual bool isUsable() const;

	virtual void resetCooldown();

	virtual float getCooldown() const = 0;

	virtual float& getCurrentCooldown() = 0;
};
