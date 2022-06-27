// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Info.h"
#include "Components/ArrowComponent.h"

#include "AISpawnPoint.generated.h"

UCLASS(Blueprintable)
class LOSTCONNECTION_API AAISpawnPoint : public AInfo
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Components, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> arrow;

public:
	AAISpawnPoint();

	~AAISpawnPoint() = default;
};
