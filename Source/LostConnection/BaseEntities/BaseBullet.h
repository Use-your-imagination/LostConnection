#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "BaseBullet.generated.h"

UCLASS()
class ABaseBullet : public APawn
{
	GENERATED_BODY()

public:
	ABaseBullet();

	virtual ~ABaseBullet() = default;
};
