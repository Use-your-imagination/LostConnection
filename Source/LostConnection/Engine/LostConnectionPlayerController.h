// Copyright (c) 2021 Use Your Imagination

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
	TObjectPtr<ALootManager> lootManager;

	TObjectPtr<class ATeleportPoint> mainTeleportFromLoadedRoom;

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

	UFUNCTION(Server, Reliable)
	void setMainTeleportFromLoadedRoom(class ATeleportPoint* teleportPoint);

	const TObjectPtr<class ATeleportPoint> getMainTeleportFromLoadedRoom() const;

	void PostSeamlessTravel() override;

	~ALostConnectionPlayerController() = default;
};
