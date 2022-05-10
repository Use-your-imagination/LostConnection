// Copyright (c) 2021 Use Your Imagination

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

class LOSTCONNECTION_API ICaster
{
	GENERATED_BODY()

protected:
	void castAbility(UBaseAbility* ability, const TFunction<void()>& callback);

	virtual float& getCurrentEnergy() = 0;

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

	UFUNCTION(Server, Reliable)
	virtual void setDuration(float newDuration);

	UFUNCTION(Server, Reliable)
	virtual void setPower(float newPower);

	UFUNCTION(Server, Reliable)
	virtual void setEnergyEfficiency(float newEnergyEfficiency);

	UFUNCTION(Server, Reliable)
	virtual void setAOE(float newAOE);

	UFUNCTION(Server, Reliable)
	virtual void setCastPoint(float newCastPoint);

	virtual void setCurrentAbility(UBaseAbility* ability);

	virtual float getEnergy() const = 0;

	virtual float getCurrentEnergy() const = 0;

	virtual float getEnergyRestorationPerSecond() const = 0;

	virtual float getCooldownReduction() const = 0;

	virtual float getDuration() const = 0;

	virtual float getPower() const = 0;

	virtual float getEnergyEfficiency() const = 0;

	virtual float getAOE() const = 0;

	virtual float getCastPoint() const = 0;

	virtual UBaseAbility* getCurrentAbility() const = 0;

	virtual UBasePassiveAbility* getPassiveAbility() const = 0;

	virtual UBaseAbility* getFirstAbility() const = 0;

	virtual UBaseAbility* getSecondAbility() const = 0;

	virtual UBaseAbility* getThirdAbility() const = 0;

	virtual UBaseUltimateAbility* getUltimateAbility() const = 0;

	virtual TArray<TWeakObjectPtr<UBaseAbility>> getAbilities() const;

	UFUNCTION()
	virtual const TArray<UAnimMontage*>& getAbilitiesAnimations() const;

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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castAbilityEventVisual(UBaseAbility* ability);

	UFUNCTION()
	virtual void cancelCurrentAbilityAnimation();
};
