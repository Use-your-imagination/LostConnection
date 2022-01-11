// Copyright (c) 2021 Use-your-imagination

#include "MultiplayerUtility.h"

#include "Characters/BaseDrone.h"
#include "Utility/Utility.h"

void MultiplayerUtility::runOnServerReliableWithMulticast(APawn* caller, const FName& methodName)
{
	ALostConnectionPlayerController* playerController = Utility::getPlayerController(caller);

	if (playerController)
	{
		playerController->runOnServerReliableWithMulticast(caller, methodName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(L"Can't cast to game state in MutliplayerUtility at %d %s %s", __LINE__, *caller->GetName(), *methodName.ToString()));
	}
}

void MultiplayerUtility::runOnServerUnreliableWithMulticast(APawn* caller, const FName& methodName)
{
	ALostConnectionPlayerController* playerController = Utility::getPlayerController(caller);

	if (playerController)
	{
		playerController->runOnServerUnreliableWithMulticast(caller, methodName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(L"Can't cast to game state in MutliplayerUtility at %d %s %s", __LINE__, *caller->GetName(), *methodName.ToString()));
	}
}

void MultiplayerUtility::runOnServerReliable(APawn* caller, const FName& methodName)
{
	ALostConnectionPlayerController* playerController = Utility::getPlayerController(caller);

	if (playerController)
	{
		playerController->runOnServerReliable(caller, methodName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(L"Can't cast to game state in MutliplayerUtility at %d %s %s", __LINE__, *caller->GetName(), *methodName.ToString()));
	}
}

void MultiplayerUtility::runOnServerUnreliable(APawn* caller, const FName& methodName)
{
	ALostConnectionPlayerController* playerController = Utility::getPlayerController(caller);

	if (playerController)
	{
		playerController->runOnServerUnreliable(caller, methodName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(L"Can't cast to game state in MutliplayerUtility at %d %s %s", __LINE__, *caller->GetName(), *methodName.ToString()));
	}
}
