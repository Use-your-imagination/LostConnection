// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerState.h"

#include "LostConnectionPlayerState.generated.h"

/**
 *
 */
UCLASS()
class LOSTCONNECTION_API ALostConnectionPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ALostConnectionPlayerState() = default;

	UFUNCTION(NetMulticast, Reliable)
	void runMulticastReliable(UObject* caller, const FName& methodName);

	UFUNCTION(Server, Reliable)
	void runOnServerReliable(UObject* caller, const FName& methodName);

	UFUNCTION(NetMulticast, Unreliable)
	void runMulticastUnreliable(UObject* caller, const FName& methodName);

	UFUNCTION(Server, Unreliable)
	void runOnServerUnreliable(UObject* caller, const FName& methodName);
};
