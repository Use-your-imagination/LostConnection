#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "EnvironmentTarget.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UEnvironmentTarget : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IEnvironmentTarget
{
	GENERATED_BODY()

public:
	IEnvironmentTarget() = default;

};
