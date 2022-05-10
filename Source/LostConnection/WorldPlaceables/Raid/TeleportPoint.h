// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "TeleportPoint.generated.h"

UCLASS()
class LOSTCONNECTION_API ATeleportPoint : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	ATeleportPoint();

	UFUNCTION(Category = UI, BlueprintImplementableEvent)
	int32 getNestingLevel() const;

	virtual ~ATeleportPoint() = default;
};
