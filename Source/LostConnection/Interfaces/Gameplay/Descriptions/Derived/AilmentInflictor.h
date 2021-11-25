// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

#include "AilmentInflictor.generated.h"

enum class typeOfDamage : uint8;

UINTERFACE(MinimalAPI)
class UAilmentInflictor : public UDamageInflictor
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IAilmentInflictor : public IDamageInflictor
{
	GENERATED_BODY()

public:
	IAilmentInflictor() = default;

	virtual void setCrushingHitChance(float crushingHitChance);

	virtual void setAdditionalCrushingHitChance(float additionalCrushingHitChance);

	virtual typeOfDamage getDamageType() const = 0;

	virtual float getCrushingHitChance() const = 0;

	virtual float getAdditionalCrushingHitChance() const = 0;

	virtual bool getCrushingHitProc() const;
};
