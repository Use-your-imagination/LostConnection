#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "PassiveAbilityCast.generated.h"

UINTERFACE(BlueprintType)
class UPassiveAbilityCast : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IPassiveAbilityCast
{
	GENERATED_BODY()

protected:
	virtual void castPassiveAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castPassiveAbilityEventVisual();

	virtual void castPassiveAbilityLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castPassiveAbilityEventLogic();

public:
	IPassiveAbilityCast() = default;

	UFUNCTION()
	virtual void castPassiveAbility();
};
