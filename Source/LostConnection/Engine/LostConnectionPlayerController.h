// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"

#include "Loot/LootManager.h"

#include "LostConnectionPlayerController.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(ReplicatedUsing = onLootManagerInit)
	ALootManager* lootManager;

protected:
	virtual void GetSeamlessTravelActorList(bool bToEntry, TArray<AActor*>& ActorList) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION()
	void onLootManagerInit();

protected:
	void BeginPlay() override;

public:
	ALostConnectionPlayerController();

	UFUNCTION(Server, Reliable)
	void respawnPlayer(const FTransform& respawnTransform);

	UFUNCTION(Category = Save, Client, Reliable, BlueprintCallable)
	void save();

	virtual ~ALostConnectionPlayerController() = default;
};
