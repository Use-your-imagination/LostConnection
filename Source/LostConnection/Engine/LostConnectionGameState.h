// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameState.h"

#include "VFX/VFXManager.h"
#include "Interfaces/Economy/LootPointsGiver.h"
#include "Interfaces/Loot/AmmoDropable.h"

#include "LostConnectionGameState.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionGameState : public AGameState
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = AI, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 totalBots;

	UPROPERTY(Category = AI, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 totalWaves;

	UPROPERTY(Category = AI, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 remainingBots;

	UPROPERTY(Category = AI, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 remainingWaves;

	UPROPERTY(Category = AI, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 currentWaveTotalBots;

	UPROPERTY(Category = AI, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 currentWaveRemainingBots;

private:
	UPROPERTY()
	TObjectPtr<UVFXManager> manager;

private:
	TArray<TSoftObjectPtr<UWorld>> usedRooms;
	TSoftObjectPtr<UWorld> lastLoadedRoom;
	bool isRoomLoaded;

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void PostInitializeComponents() override;

private:
	void loadRoom(FTransform&& spawnTransform);

	void clearRoom();

	UFUNCTION(NetMulticast, Unreliable)
	void spawnVFXAtLocationMulticast(const FVector& location, UNiagaraSystem* vfx);

	UFUNCTION(NetMulticast, Unreliable)
	void spawnVFXAtTransformMulticast(const FTransform& transform, UNiagaraSystem* vfx);

	UFUNCTION(Server, Reliable)
	void giveEachPlayerLootPoints(int32 count);

public:
	ALostConnectionGameState();

	UFUNCTION(Category = RoomLoading, Server, Reliable, BlueprintCallable)
	void startRoomLoading();

	UFUNCTION(Category = VFX, Server, Unreliable, BlueprintCallable)
	void spawnVFXAtLocation(const FVector& location, UNiagaraSystem* vfx);

	UFUNCTION(Category = VFX, Server, Unreliable, BlueprintCallable)
	void spawnVFXAtTransform(const FTransform& transform, UNiagaraSystem* vfx);

	void verteilenLootPoints(ILootPointsGiver* giver);

	void dropAmmo(IAmmoDropable* ammoDropable);

	int32& getTotalBots();

	int32& getTotalWaves();

	int32& getRemainingBots();

	int32& getRemainingWaves();

	int32& getCurrentWaveTotalBots();

	int32& getCurrentWaveRemainingBots();

	const TSoftObjectPtr<UWorld>& getLastLoadedRoom() const;

	template<typename T>
	T* spawn(UClass* subclass, const FTransform& transform, ESpawnActorCollisionHandlingMethod spawnMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	template<typename T>
	T* spawn(const FTransform& transform, ESpawnActorCollisionHandlingMethod spawnMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	virtual void Tick(float DeltaTime) override;
};

template<typename T>
T* ALostConnectionGameState::spawn(UClass* subclass, const FTransform& transform, ESpawnActorCollisionHandlingMethod spawnMethod)
{
	return GetWorld()->SpawnActorDeferred<T>(subclass, transform, nullptr, nullptr, spawnMethod);
}

template<typename T>
T* ALostConnectionGameState::spawn(const FTransform& transform, ESpawnActorCollisionHandlingMethod spawnMethod)
{
	return GetWorld()->SpawnActorDeferred<T>(T::StaticClass(), transform, nullptr, nullptr, spawnMethod);
}
