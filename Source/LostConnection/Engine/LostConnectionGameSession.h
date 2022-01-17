// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameSession.h"

#include "LostConnectionGameSession.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionGameSession : public AGameSession
{
	GENERATED_BODY()
	
public:
	ALostConnectionGameSession(const FObjectInitializer& objectInitializer);

	bool KickPlayer(APlayerController* KickedPlayer, const FText& KickReason) override;
};
