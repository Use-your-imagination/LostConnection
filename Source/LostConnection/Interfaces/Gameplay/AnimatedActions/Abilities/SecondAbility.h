#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "SecondAbility.generated.h"

UINTERFACE(BlueprintType)
class USecondAbility : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTCONNECTION_API ISecondAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void useSecondAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void useSecondAbilityEventVisual();

	UFUNCTION()
	virtual void useSecondAbilityLogic(class ABaseCharacter* target) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void useSecondAbilityEventLogic(class ABaseCharacter* target);

public:
	ISecondAbility() = default;

	UFUNCTION()
	virtual void useSecondAbility();
};
