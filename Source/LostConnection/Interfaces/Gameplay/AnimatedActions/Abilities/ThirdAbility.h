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
	virtual void thirdAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void thirdAbilityEventVisual();

	UFUNCTION()
	virtual void thirdAbilityLogic(class ABaseCharacter* target) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void thirdAbilityEventLogic(class ABaseCharacter* target);

public:
	IThirdAbility() = default;

	UFUNCTION()
	virtual void thirdAbility();
};
