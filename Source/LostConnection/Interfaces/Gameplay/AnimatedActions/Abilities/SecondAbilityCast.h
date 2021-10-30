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

private:
	UFUNCTION()
	virtual void callCastSecondAbilityEventVisual();

protected:
	UFUNCTION()
	virtual void castSecondAbilityVisual();

	virtual void castSecondAbilityLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castSecondAbilityEventLogic();

	virtual bool checkSecondAbilityCast() const = 0;

public:
	ISecondAbilityCast() = default;

	UFUNCTION()
	virtual void castSecondAbility();
};
