#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "StatusInflictor.generated.h"

enum class typeOfDamage : uint8;

UINTERFACE(MinimalAPI)
class UStatusInflictor : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IStatusInflictor
{
	GENERATED_BODY()

public:
	IStatusInflictor() = default;

	virtual float getInflictorDamage() const = 0;

	virtual typeOfDamage getDamageType() const = 0;

	virtual bool getCrushingHitProc() const = 0;
};
