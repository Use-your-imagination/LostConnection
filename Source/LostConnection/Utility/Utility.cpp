#include "Utility.h"

#include "Characters/BaseDrone.h"

UWorld* Utility::getWorld()
{
	return ABaseDrone::globalPlayerPtr->GetWorld();
}

ALostConnectionGameState* Utility::getGameState()
{
	return Utility::getWorld()->GetGameState<ALostConnectionGameState>();
}
