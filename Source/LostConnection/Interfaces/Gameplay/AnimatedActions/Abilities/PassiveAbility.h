#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "PassiveAbility.generated.h"

UINTERFACE(BlueprintType)
class UPassiveAbility : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTCONNECTION_API IPassiveAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void usePassiveAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void usePassiveAbilityEventVisual();

	UFUNCTION()
	virtual void usePassiveAbilityLogic(class ABaseCharacter* target) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void usePassiveAbilityEventLogic(class ABaseCharacter* target);

public:
	IPassiveAbility() = default;

	UFUNCTION()
	virtual void usePassiveAbility();
};
