// Copyright (c) 2021 Use-your-imagination

#include "Utility.h"

#include "Algo/Count.h"

#include "Interfaces/Gameplay/Descriptions/Derived/StatusReceiver.h"

ALostConnectionGameState* Utility::getGameState(APawn* pawn)
{
	return pawn->GetWorld()->GetGameState<ALostConnectionGameState>();
}

ALostConnectionPlayerState* Utility::getPlayerState(APawn* pawn)
{
	return pawn->GetController()->GetPlayerState<ALostConnectionPlayerState>();
}

SIZE_T Utility::countStatuses(const IStatusReceiver* target, UClass* statusStaticClass)
{
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	return Algo::CountIf(statuses, [&statusStaticClass](const class UBaseStatus* status) { return status->StaticClass()->IsChildOf(statusStaticClass); });
}
