// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"

#include "AISpawnPoint.generated.h"

UCLASS(Blueprintable)
class LOSTCONNECTION_API AAISpawnPoint : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Components, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	UArrowComponent* arrow;

public:
	AAISpawnPoint();

	virtual ~AAISpawnPoint() = default;
};
