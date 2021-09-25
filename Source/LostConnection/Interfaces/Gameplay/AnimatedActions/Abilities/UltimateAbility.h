#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "UltimateAbility.generated.h"

UINTERFACE(BlueprintType)
class UUltimateAbility : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTCONNECTION_API IUltimateAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void ultimateAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ultimateAbilityEventVisual();

	UFUNCTION()
	virtual void ultimateAbilityLogic(class ABaseCharacter* target) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ultimateAbilityEventLogic(class ABaseCharacter* target);

public:
	IUltimateAbility() = default;

	UFUNCTION()
	virtual void ultimateAbility();
};
