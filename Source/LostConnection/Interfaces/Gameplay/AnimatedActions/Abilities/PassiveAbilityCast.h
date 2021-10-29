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

private:
	UFUNCTION()
	virtual void callCastPassiveAbilityEventVisual();

protected:
	UFUNCTION()
	virtual void castPassiveAbilityVisual();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castPassiveAbilityEventVisual();

	virtual void castPassiveAbilityLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castPassiveAbilityEventLogic();

	virtual bool checkPassiveAbilityCast() const = 0;

public:
	IPassiveAbilityCast() = default;

	UFUNCTION()
	virtual void castPassiveAbility();
};
