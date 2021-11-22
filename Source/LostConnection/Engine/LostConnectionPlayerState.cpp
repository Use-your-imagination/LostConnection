// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionPlayerState.h"

void ALostConnectionPlayerState::runMulticastReliable_Implementation(AActor* caller, const FName& methodName)
{
	if (!caller)
	{
		return;
	}

	FTimerDelegate delegate;

	delegate.BindUFunction(caller, methodName);

	delegate.Execute();
}

void ALostConnectionPlayerState::runMulticastUnreliable_Implementation(AActor* caller, const FName& methodName)
{
	if (!caller)
	{
		return;
	}

	FTimerDelegate delegate;

	delegate.BindUFunction(caller, methodName);

	delegate.Execute();
}

void ALostConnectionPlayerState::runOnServerReliableWithMulticast_Implementation(AActor* caller, const FName& methodName)
{
	this->runMulticastReliable(caller, methodName);
}

void ALostConnectionPlayerState::runOnServerUnreliableWithMulticast_Implementation(AActor* caller, const FName& methodName)
{
	this->runMulticastUnreliable(caller, methodName);
}

void ALostConnectionPlayerState::runOnServerReliable_Implementation(AActor* caller, const FName& methodName)
{
	if (!caller)
	{
		return;
	}

	FTimerDelegate delegate;

	delegate.BindUFunction(caller, methodName);

	delegate.Execute();
}

void ALostConnectionPlayerState::runOnServerUnreliable_Implementation(AActor* caller, const FName& methodName)
{
	if (!caller)
	{
		return;
	}

	FTimerDelegate delegate;

	delegate.BindUFunction(caller, methodName);

	delegate.Execute();
}
