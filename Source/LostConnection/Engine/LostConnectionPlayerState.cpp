#include "LostConnectionPlayerState.h"

void ALostConnectionPlayerState::runMulticastReliable_Implementation(UObject* caller, const FName& methodName)
{
	FTimerDelegate delegate;

	delegate.BindUFunction(caller, methodName);

	delegate.Execute();
}

void ALostConnectionPlayerState::runMulticastUnreliable_Implementation(UObject* caller, const FName& methodName)
{
	FTimerDelegate delegate;

	delegate.BindUFunction(caller, methodName);

	delegate.Execute();
}

void ALostConnectionPlayerState::runOnServerReliable_Implementation(UObject* caller, const FName& methodName)
{
	this->runMulticastReliable(caller, methodName);
}

void ALostConnectionPlayerState::runOnServerUnreliable_Implementation(UObject* caller, const FName& methodName)
{
	this->runMulticastUnreliable(caller, methodName);
}
