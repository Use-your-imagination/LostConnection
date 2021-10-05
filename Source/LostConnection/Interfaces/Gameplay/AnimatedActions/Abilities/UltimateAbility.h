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
	virtual void useUltimateAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void useUltimateAbilityEventVisual();

	UFUNCTION()
	virtual void useUltimateAbilityLogic(class ABaseCharacter* target) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void useUltimateAbilityEventLogic(class ABaseCharacter* target);

public:
	IUltimateAbility() = default;

	UFUNCTION()
	virtual void useUltimateAbility();
};
