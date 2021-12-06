// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"

#include "LevelCreationWaypoint.generated.h"

UCLASS(Blueprintable)
class LOSTCONNECTION_API ALevelCreationWaypoint : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Components, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	UArrowComponent* arrow;

	bool isUsed;

private:
	void BeginPlay() override;

public:
	ALevelCreationWaypoint();

	void use();

	bool getIsUsed() const;

	virtual ~ALevelCreationWaypoint() = default;
};
