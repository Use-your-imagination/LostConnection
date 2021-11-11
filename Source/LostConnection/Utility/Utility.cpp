#include "Utility.h"

#include "Characters/BaseDrone.h"

UWorld* Utility::getWorld()
{
	return ABaseDrone::globalPlayerPtr->GetWorld();
}
