// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Cooldownable.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UCooldownable : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ICooldownable
{
	GENERATED_BODY()

public:
	ICooldownable() = default;

	/**
	* Must be called on server
	* @param startCooldown If Start Cooldown < 0.0 set cooldown to GetCooldown() return value otherwise set cooldown to Start Cooldown
	*/
	UFUNCTION(Category = Cooldown, BlueprintCallable)
	virtual void startCooldown(float startCooldown = -1.0f);

	virtual void processCooldown(float DeltaTime);

	UFUNCTION(Category = Cooldown, BlueprintCallable)
	virtual bool isUsable() const;

	virtual void resetCooldown();

	UFUNCTION(Category = Cooldown, BlueprintCallable)
	virtual float getCooldown() const = 0;

	virtual float& getCurrentCooldownReference() = 0;

	UFUNCTION(Category = Cooldown, BlueprintCallable)
	virtual float getCurrentCooldown() const = 0;

	// Value between 0 and 1
	UFUNCTION(Category = Cooldown, BlueprintCallable)
	virtual float getCooldownState() const;
};

inline void ICooldownable::processCooldown(float DeltaTime)
{
	float& currentCooldown = this->getCurrentCooldownReference();

	if (currentCooldown)
	{
		currentCooldown = FMath::Max(0.0f, currentCooldown - DeltaTime);
	}
}

inline bool ICooldownable::isUsable() const
{
	return this->getCurrentCooldown() == 0.0f;
}

inline float ICooldownable::getCooldownState() const
{
	return this->getCurrentCooldown() / this->getCooldown();
}
