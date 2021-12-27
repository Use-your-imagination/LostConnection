// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Interfaces/Gameplay/Descriptions/Actionable.h"
#include "Characters/BaseDrone.h"

#include "ChooseLevelConsole.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API AChooseLevelConsole :
	public AActor,
	public IActionable
{
	GENERATED_BODY()
	
public:	
	AChooseLevelConsole() = default;

	virtual void action(ABaseDrone* player) final;

	virtual ~AChooseLevelConsole() = default;
};
