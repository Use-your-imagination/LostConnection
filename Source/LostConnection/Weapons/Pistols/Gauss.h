#pragma once

#include "CoreMinimal.h"

#include "Weapons/BaseWeapon.h"

#include "Gauss.generated.h"

UCLASS()
class LOSTCONNECTION_API UGauss : public UBaseWeapon
{
	GENERATED_BODY()

public:
	UGauss();

	~UGauss() = default;
};
