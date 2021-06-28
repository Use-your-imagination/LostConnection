#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "BaseBullet.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseBullet : public APawn
{
	GENERATED_BODY()

public:
	ABaseBullet();

	virtual ~ABaseBullet() = default;
};
