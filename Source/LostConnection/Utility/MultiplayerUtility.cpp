// Copyright (c) 2021 Use-your-imagination

#include "MultiplayerUtility.h"

#include "Characters/BaseDrone.h"
#include "Utility/Utility.h"

void MultiplayerUtility::runOnServerReliableWithMulticast(APawn* caller, const FName& methodName)
{
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(caller);

	if (playerState)
	{
		playerState->runOnServerReliableWithMulticast(caller, methodName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Can't cast to player state in MutliplayerUtility at %d %s %s"), __LINE__, *caller->GetName(), *methodName.ToString()));
	}
}

void MultiplayerUtility::runOnServerUnreliableWithMulticast(APawn* caller, const FName& methodName)
{
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(caller);

	if (playerState)
	{
		playerState->runOnServerUnreliableWithMulticast(caller, methodName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Can't cast to player state in MutliplayerUtility at %d %s %s"), __LINE__, *caller->GetName(), *methodName.ToString()));
	}
}

void MultiplayerUtility::runOnServerReliable(APawn* caller, const FName& methodName)
{
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(caller);

	if (playerState)
	{
		playerState->runOnServerReliable(caller, methodName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Can't cast to player state in MutliplayerUtility at %d %s %s"), __LINE__, *caller->GetName(), *methodName.ToString()));
	}
}

void MultiplayerUtility::runOnServerUnreliable(APawn* caller, const FName& methodName)
{
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(caller);

	if (playerState)
	{
		playerState->runOnServerUnreliable(caller, methodName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Can't cast to player state in MutliplayerUtility at %d %s %s"), __LINE__, *caller->GetName(), *methodName.ToString()));
	}
}
