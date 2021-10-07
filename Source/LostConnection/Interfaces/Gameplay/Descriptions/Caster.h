#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Abilities/BasePassiveAbility.h"
#include "Abilities/BaseUltimateAbility.h"

#include "Caster.generated.h"

UINTERFACE(BlueprintType)
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

	UFUNCTION(Server, Reliable)
	virtual void setEnergy(float newEnergy);

	UFUNCTION(Server, Reliable)
	virtual void setCurrentEnergy(float newCurrentEnergy);

	UFUNCTION(Server, Reliable)
	virtual void setEnergyRestorationPerSecond(float newEnergyRestorationPerSecond);

	UFUNCTION(Server, Reliable)
	virtual void setCooldownReduction(float newCooldownReduction);

	virtual float getEnergy() const = 0;

	virtual float getCurrentEnergy() const = 0;

	virtual float getEnergyRestorationPerSecond() const = 0;

	virtual float getCooldownReduction() const = 0;

	virtual ABasePassiveAbility* getPassiveAbility() = 0;

	virtual ABaseAbility* getFirstAbility() = 0;

	virtual ABaseAbility* getSecondAbility() = 0;

	virtual ABaseAbility* getThirdAbility() = 0;

	virtual ABaseUltimateAbility* getUltimateAbility() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void applyPassiveAbilityEvent(class ABaseCharacter* target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void applyFirstAbilityEvent(class ABaseCharacter* target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void applySecondAbilityEvent(class ABaseCharacter* target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void applyThirdAbilityEvent(class ABaseCharacter* target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void applyUltimateAbilityEvent(class ABaseCharacter* target);
};
