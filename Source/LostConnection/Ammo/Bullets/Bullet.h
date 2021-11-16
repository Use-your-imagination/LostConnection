#pragma once

#include "CoreMinimal.h"

#include "Ammo/BaseAmmo.h"

#include "Bullet.generated.h"

UCLASS()
class LOSTCONNECTION_API ABullet : public ABaseAmmo
{
	GENERATED_BODY()

public:
	ABullet();

	~ABullet() = default;
};
