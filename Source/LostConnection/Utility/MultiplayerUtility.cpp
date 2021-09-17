// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerUtility.h"

#include "Characters/LostConnectionCharacter.h"
#include "Engine/LostConnectionPlayerState.h"

void MultiplayerUtility::runOnServerReliableWithMulticast(UObject* caller, const FName& methodName)
{
	ALostConnectionPlayerState* playerState = ALostConnectionCharacter::globalPlayerPtr->GetPlayerState<ALostConnectionPlayerState>();

	if (playerState)
	{
		playerState->runOnServerReliableWithMulticast(caller, methodName);
	}
}

void MultiplayerUtility::runOnServerUnreliableWithMulticast(UObject* caller, const FName& methodName)
{
	ALostConnectionPlayerState* playerState = ALostConnectionCharacter::globalPlayerPtr->GetPlayerState<ALostConnectionPlayerState>();

	if (playerState)
	{
		playerState->runOnServerUnreliableWithMulticast(caller, methodName);
	}
}

void MultiplayerUtility::runOnServerReliable(UObject* caller, const FName& methodName)
{
	ALostConnectionPlayerState* playerState = ALostConnectionCharacter::globalPlayerPtr->GetPlayerState<ALostConnectionPlayerState>();

	if (playerState)
	{
		playerState->runOnServerReliable(caller, methodName);
	}
}

void MultiplayerUtility::runOnServerUnreliable(UObject* caller, const FName& methodName)
{
	ALostConnectionPlayerState* playerState = ALostConnectionCharacter::globalPlayerPtr->GetPlayerState<ALostConnectionPlayerState>();

	if (playerState)
	{
		playerState->runOnServerUnreliable(caller, methodName);
	}
}
