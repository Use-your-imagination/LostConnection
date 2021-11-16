#include "Utility.h"

ALostConnectionGameState* Utility::getGameState(APawn* pawn)
{
	return pawn->GetWorld()->GetGameState<ALostConnectionGameState>();
}

ALostConnectionPlayerState* Utility::getPlayerState(APawn* pawn)
{
	return pawn->GetController()->GetPlayerState<ALostConnectionPlayerState>();
}
