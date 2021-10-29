#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "FirstAbilityCast.generated.h"

UINTERFACE(BlueprintType)
class UFirstAbilityCast : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IFirstAbilityCast
{
	GENERATED_BODY()

private:
	UFUNCTION()
	virtual void callCastFirstAbilityEventVisual();

protected:
	UFUNCTION()
	virtual void castFirstAbilityVisual();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castFirstAbilityEventVisual();

	virtual void castFirstAbilityLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castFirstAbilityEventLogic();

	virtual bool checkFirstAbilityCast() const = 0;

public:
	IFirstAbilityCast() = default;

	UFUNCTION()
	virtual void castFirstAbility();
};
