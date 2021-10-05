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

protected:
	UFUNCTION()
	virtual void castFirstAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castFirstAbilityEventVisual();

	UFUNCTION()
	virtual void castFirstAbilityLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castFirstAbilityEventLogic();

public:
	IFirstAbilityCast() = default;

	UFUNCTION()
	virtual void castFirstAbility();
};
