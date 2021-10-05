#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "UltimateAbilityCast.generated.h"

UINTERFACE(BlueprintType)
class UUltimateAbilityCast : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IUltimateAbilityCast
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void castUltimateAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castUltimateAbilityEventVisual();

	UFUNCTION()
	virtual void castUltimateAbilityLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castUltimateAbilityEventLogic();

public:
	IUltimateAbilityCast() = default;

	UFUNCTION()
	virtual void castUltimateAbility();
};
