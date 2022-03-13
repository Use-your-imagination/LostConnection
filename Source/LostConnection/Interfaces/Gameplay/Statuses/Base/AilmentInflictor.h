// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "StatusInflictor.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "AilmentInflictor.generated.h"

UINTERFACE(MinimalAPI)
class UAilmentInflictor : public UStatusInflictor
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IAilmentInflictor : public IStatusInflictor
{
	GENERATED_BODY()

public:
	IAilmentInflictor() = default;

	virtual void setCrushingHitChance(float crushingHitChance);

	virtual void setAdditionalCrushingHitChance(float additionalCrushingHitChance);

	virtual ETypeOfDamage getDamageType() const = 0;

	virtual float getCrushingHitChance() const = 0;

	virtual float getAdditionalCrushingHitChance() const = 0;

	virtual bool getCrushingHitProc() const;
};
