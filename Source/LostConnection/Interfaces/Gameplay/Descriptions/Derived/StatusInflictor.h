#pragma once

#include "CoreMinimal.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

#include "StatusInflictor.generated.h"

enum class typeOfDamage : uint8;

UINTERFACE(MinimalAPI)
class UStatusInflictor : public UDamageInflictor
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IStatusInflictor : public IDamageInflictor
{
	GENERATED_BODY()

public:
	IStatusInflictor() = default;

	virtual typeOfDamage getDamageType() const = 0;
};
