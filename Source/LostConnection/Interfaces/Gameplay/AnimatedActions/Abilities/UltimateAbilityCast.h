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

private:
	UFUNCTION()
	virtual void callCastUltimateAbilityEventVisual();

protected:
	UFUNCTION()
	virtual void castUltimateAbilityVisual();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castUltimateAbilityEventVisual();

	virtual void castUltimateAbilityLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castUltimateAbilityEventLogic();

	virtual bool checkUltimateAbilityCast() const = 0;

public:
	IUltimateAbilityCast() = default;

	UFUNCTION()
	virtual void castUltimateAbility();
};
