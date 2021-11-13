#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "StatusInflictor.generated.h"

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
};
