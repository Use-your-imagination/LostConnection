#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerState.h"

#include "LostConnectionPlayerState.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	UFUNCTION(NetMulticast, Reliable)
	void runMulticastReliable(AActor* caller, const FName& methodName);

	UFUNCTION(NetMulticast, Unreliable)
	void runMulticastUnreliable(AActor* caller, const FName& methodName);

public:
	ALostConnectionPlayerState() = default;

	UFUNCTION(Server, Reliable)
	void runOnServerReliableWithMulticast(AActor* caller, const FName& methodName);

	UFUNCTION(Server, Unreliable)
	void runOnServerUnreliableWithMulticast(AActor* caller, const FName& methodName);

	UFUNCTION(Server, Reliable)
	void runOnServerReliable(AActor* caller, const FName& methodName);

	UFUNCTION(Server, Unreliable)
	void runOnServerUnreliable(AActor* caller, const FName& methodName);
};
