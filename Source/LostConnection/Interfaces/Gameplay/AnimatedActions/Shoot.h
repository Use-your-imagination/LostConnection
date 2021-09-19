#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Shoot.generated.h"

UINTERFACE(BlueprintType)
class UShoot : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTCONNECTION_API IShoot
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void shootVisual() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void shootEventVisual();

	UFUNCTION()
	virtual void shootLogic() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void shootEventLogic();

public:
	IShoot() = default;
};
