#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Caster.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UCaster : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTCONNECTION_API ICaster
{
	GENERATED_BODY()

public:
	ICaster() = default;

	UFUNCTION()
	virtual void usePassiveAbility() = 0;

	UFUNCTION()
	virtual void useFirstAbility() = 0;

	UFUNCTION()
	virtual void useSecondAbility() = 0;

	UFUNCTION()
	virtual void useThirdAbility() = 0;

	UFUNCTION()
	virtual void useUltimateAbility() = 0;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void setEnergy(float newEnergy) = 0;

	UFUNCTION(BlueprintCallable)
	virtual float getEnergy() const = 0;
};
