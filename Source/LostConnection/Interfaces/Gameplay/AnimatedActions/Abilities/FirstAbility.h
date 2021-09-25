#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "FirstAbility.generated.h"

UINTERFACE(BlueprintType)
class UFirstAbility : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTCONNECTION_API IFirstAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void firstAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void firstAbilityEventVisual();

	UFUNCTION()
	virtual void firstAbilityLogic(class ABaseCharacter* target) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void firstAbilityEventLogic(class ABaseCharacter* target);

public:
	IFirstAbility() = default;

	UFUNCTION()
	virtual void firstAbility();
};
