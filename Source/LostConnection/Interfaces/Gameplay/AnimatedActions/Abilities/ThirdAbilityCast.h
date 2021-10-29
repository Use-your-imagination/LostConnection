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

private:
	UFUNCTION()
	virtual void callCastThirdAbilityEventVisual();

protected:
	UFUNCTION()
	virtual void castThirdAbilityVisual();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castThirdAbilityEventVisual();

	virtual void castThirdAbilityLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void castThirdAbilityEventLogic();

	virtual bool checkThirdAbilityCast() const = 0;

public:
	IThirdAbilityCast() = default;

	UFUNCTION()
	virtual void castThirdAbility();
};
