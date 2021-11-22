// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameStateBase.h"

#include "LostConnectionGameState.generated.h"

enum class typeOfDamage : uint8;

UCLASS()
class LOSTCONNECTION_API ALostConnectionGameState : public AGameStateBase
{
	GENERATED_BODY()
	
private:
	TMap<typeOfDamage, UClass*> statuses;

public:
	ALostConnectionGameState();

	UClass* getDefaultStatus(typeOfDamage damageType) const;

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
