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
	virtual void secondAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void secondAbilityEventVisual();

	UFUNCTION()
	virtual void secondAbilityLogic(class ABaseCharacter* target) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void secondAbilityEventLogic(class ABaseCharacter* target);

public:
	ISecondAbility() = default;

	UFUNCTION()
	virtual void secondAbility();
};
