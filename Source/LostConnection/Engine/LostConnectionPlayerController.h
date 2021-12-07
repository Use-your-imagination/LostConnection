// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "LostConnectionPlayerController.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void GetSeamlessTravelActorList(bool bToEntry, TArray<AActor*>& ActorList) override;

public:
	ALostConnectionPlayerController();
};
