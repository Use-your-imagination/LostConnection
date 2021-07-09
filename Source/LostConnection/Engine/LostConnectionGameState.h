// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameStateBase.h"

#include "LostConnectionGameState.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ALostConnectionGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ALostConnectionGameState() = default;

	template<typename T>
	T* spawn(UClass* staticClass, const FVector& location, const FRotator& rotation);
};

template<typename T>
T* ALostConnectionGameState::spawn(UClass* staticClass, const FVector& location, const FRotator& rotation)
{
	FActorSpawnParameters parameters;

	parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	parameters.bNoFail = true;

	return GetWorld()->SpawnActor<T>(staticClass, location, rotation, parameters);
}
