#pragma once

#include "CoreMinimal.h"

#include "Ammo/BaseAmmo.h"

#include "Ball.generated.h"

UCLASS()
class LOSTCONNECTION_API ABall : public ABaseAmmo
{
	GENERATED_BODY()
	
public:
	ABall();

	~ABall() = default;
};
