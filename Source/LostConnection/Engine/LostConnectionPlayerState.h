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
	ALostConnectionPlayerState();

	template<typename T>
	T* spawn(UClass* staticClass, const FVector& location, const FRotator& rotation);
};

template<typename T>
T* ALostConnectionPlayerState::spawn(UClass* staticClass, const FVector& location, const FRotator& rotation)
{
	return GetWorld()->SpawnActor<T>(staticClass, location, rotation);
}