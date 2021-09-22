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
	virtual void passiveAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void passiveAbilityEventVisual();

	UFUNCTION()
	virtual void passiveAbilityLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void passiveAbilityEventLogic();

public:
	IPassiveAbility() = default;

	UFUNCTION()
	virtual void passiveAbility();
};
