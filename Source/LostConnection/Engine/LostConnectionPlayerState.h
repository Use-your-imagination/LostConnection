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

	template<typename... Args>
	UFUNCTION(NetMulticast, Reliable)
	void runMulticastReliable(UObject* caller, const FName& methodName, Args&&... args)
	{
		FTimerDelegate delegate;

		delegate.BindUFunction(caller, methodName, std::forward<Args...>(args)...);

		delegate.Execute();
	}

	template<typename... Args>
	UFUNCTION(Server, Reliable)
	void runOnServerReliable(UObject* caller, const FName& methodName, Args&&... args)
	{
		this->runMulticastReliable(caller, methodName, std::forward<Args...>(args)...);
	}

	template<typename... Args>
	UFUNCTION(NetMulticast, Unreliable)
	void runMulticastUnreliable(UObject* caller, const FName& methodName, Args&&... args)
	{
		FTimerDelegate delegate;

		delegate.BindUFunction(caller, methodName, std::forward<Args...>(args)...);

		delegate.Execute();
	}

	template<typename... Args>
	UFUNCTION(Server, Unreliable)
	void runOnServerUnreliable(UObject* caller, const FName& methodName, Args&&... args)
	{
		this->runMulticastUnreliable(caller, methodName, std::forward<Args...>(args)...);
	}
};
