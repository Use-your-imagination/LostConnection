// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerUtility.h"

#include "Character/LostConnectionCharacter.h"
#include "Engine/LostConnectionPlayerState.h"

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
