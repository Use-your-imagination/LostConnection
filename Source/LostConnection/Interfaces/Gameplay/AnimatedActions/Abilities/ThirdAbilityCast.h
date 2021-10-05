#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "ThirdAbilityCast.generated.h"

UINTERFACE(BlueprintType)
class UThirdAbilityCast : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IThirdAbilityCast
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void castThirdAbilityVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castThirdAbilityEventVisual();

	UFUNCTION()
	virtual void castThirdAbilityLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castThirdAbilityEventLogic();

public:
	IThirdAbilityCast() = default;

	UFUNCTION()
	virtual void castThirdAbility();
};
