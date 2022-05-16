// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "BaseGrapple.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseGrapple : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Grapple, Instanced, BlueprintReadOnly, Meta = (ExposeOnSpawn = "true"))
	TObjectPtr<class UBaseGrappleHandler> handler;
	
public:	
	ABaseGrapple() = default;

	UFUNCTION(Category = Grapple, BlueprintCallable, Server, Unreliable)
	void callPullupLock();

	UFUNCTION(Category = Grapple, BlueprintImplementableEvent)
	void pullupLock();

	virtual ~ABaseGrapple() = default;
};
