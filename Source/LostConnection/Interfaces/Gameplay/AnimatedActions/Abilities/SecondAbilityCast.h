#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "SecondAbilityCast.generated.h"

UINTERFACE(BlueprintType)
class USecondAbilityCast : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ISecondAbilityCast
{
	GENERATED_BODY()

protected:
	virtual void castSecondAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castSecondAbilityEventVisual();

	virtual void castSecondAbilityLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castSecondAbilityEventLogic();

public:
	ISecondAbilityCast() = default;

	UFUNCTION()
	virtual void castSecondAbility();
};
