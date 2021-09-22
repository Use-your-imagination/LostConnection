#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Abilities/BasePassiveAbility.h"
#include "Abilities/BaseUltimateAbility.h"

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

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void setEnergy(float newEnergy) = 0;

	UFUNCTION(BlueprintCallable)
	virtual float getEnergy() const = 0;

	virtual ABasePassiveAbility* getPassiveAbility() = 0;

	virtual ABaseAbility* getFirstAbility() = 0;

	virtual ABaseAbility* getSecondAbility() = 0;

	virtual ABaseAbility* getThirdAbility() = 0;

	virtual ABaseUltimateAbility* getUltimateAbility() = 0;
};
