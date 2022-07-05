// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "StatusInflictor.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "AilmentInflictor.generated.h"

UINTERFACE(BlueprintType)
class UAilmentInflictor : public UStatusInflictor
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IAilmentInflictor : public IStatusInflictor
{
	GENERATED_BODY()

public:
	IAilmentInflictor() = default;

	virtual void setBaseCrushingHitChance(float crushingHitChance);

	virtual void setAdditionalCrushingHitChance(float additionalCrushingHitChance);

	virtual void setDamageType(ETypeOfDamage type);

	virtual ETypeOfDamage getDamageType() const = 0;

	virtual float getBaseCrushingHitChance() const = 0;

	virtual float getAdditionalCrushingHitChance() const = 0;

	virtual bool getCrushingHitProc() const;
};
