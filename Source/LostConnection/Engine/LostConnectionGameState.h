// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"

#include "LostConnectionGameState.generated.h"

enum class typeOfDamage : uint8;

UCLASS()
class LOSTCONNECTION_API ALostConnectionGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	TArray<TSoftObjectPtr<UWorld>> usedRooms;

	UPROPERTY(Category = RoomLoading, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	bool isLastRoomLoaded;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	void loadRoom(const TSoftObjectPtr<UWorld>& room, FVector location, FRotator rotation);

public:
	ALostConnectionGameState();

	UFUNCTION(Category = RoomLoading, BlueprintCallable)
	void startRoomLoading();

	/// @brief Spawn actor deferred
	/// @tparam T 
	/// @param staticClass 
	/// @param transform 
	/// @return 
	template<typename T>
	T* spawn(UClass* staticClass, const FTransform& transform, ESpawnActorCollisionHandlingMethod spawnMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	/// @brief Spawn actor deferred
	/// @tparam T 
	/// @param staticClass 
	/// @param transform 
	/// @return 
	template<typename T>
	T* spawn(const FTransform& transform, ESpawnActorCollisionHandlingMethod spawnMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
};

template<typename T>
T* ALostConnectionGameState::spawn(UClass* staticClass, const FTransform& transform, ESpawnActorCollisionHandlingMethod spawnMethod)
{
	return GetWorld()->SpawnActorDeferred<T>(staticClass, transform, nullptr, nullptr, spawnMethod);
}

template<typename T>
T* ALostConnectionGameState::spawn(const FTransform& transform, ESpawnActorCollisionHandlingMethod spawnMethod)
{
	return GetWorld()->SpawnActorDeferred<T>(T::StaticClass(), transform, nullptr, nullptr, spawnMethod);
}
