#pragma once

#include "CoreMinimal.h"

#include "Weapons/BaseWeapon.h"

#include "Hipter.generated.h"

UCLASS()
class LOSTCONNECTION_API UHipter : public UBaseWeapon
{
	GENERATED_BODY()
	
public:
	UHipter();

	~UHipter() = default;
};
