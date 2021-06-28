#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "BaseWeapon.generated.h"

UCLASS()
class ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ABaseWeapon();

	virtual ~ABaseWeapon() = default;
};
