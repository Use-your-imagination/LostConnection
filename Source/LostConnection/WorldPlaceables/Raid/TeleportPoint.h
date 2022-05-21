// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "TeleportPoint.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API ATeleportPoint : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = UI, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWorld> room;

protected:
	virtual void BeginPlay() override;

public:
	ATeleportPoint();

	UFUNCTION(Server, Reliable)
	void teleport(APlayerController* controller);

	UFUNCTION(Category = UI, BlueprintImplementableEvent, BlueprintCallable)
	int32 getNestingLevel() const;

	const TSoftObjectPtr<UWorld>& getRoom() const;

	virtual ~ATeleportPoint() = default;
};
