#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "ThirdAbility.generated.h"

UINTERFACE(BlueprintType)
class UThirdAbility : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTCONNECTION_API IThirdAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void useThirdAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void useThirdAbilityEventVisual();

	UFUNCTION()
	virtual void useThirdAbilityLogic(class ABaseCharacter* target) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void useThirdAbilityEventLogic(class ABaseCharacter* target);

public:
	IThirdAbility() = default;

	UFUNCTION()
	virtual void useThirdAbility();
};
