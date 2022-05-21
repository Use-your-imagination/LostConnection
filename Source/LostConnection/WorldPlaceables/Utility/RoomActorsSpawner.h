// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "RoomActorsSpawner.generated.h"

UCLASS()
class LOSTCONNECTION_API ARoomActorsSpawner : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Spawning, EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> actorClass;

protected:
	void BeginPlay() override;

public:	
	ARoomActorsSpawner() = default;

	~ARoomActorsSpawner() = default;
};
