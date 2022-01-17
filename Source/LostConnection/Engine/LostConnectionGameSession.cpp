// Copyright (c) 2022 Use-your-imagination

#include "LostConnectionGameSession.h"

ALostConnectionGameSession::ALostConnectionGameSession(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{

}

bool ALostConnectionGameSession::KickPlayer(APlayerController* KickedPlayer, const FText& KickReason)
{
	return Super::KickPlayer(KickedPlayer, KickReason);
}
