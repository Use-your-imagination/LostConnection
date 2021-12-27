// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Interfaces/Gameplay/Descriptions/Actionable.h"
#include "Characters/BaseDrone.h"

#include "ChooseActConsole.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API AChooseActConsole :
	public AActor,
	public IActionable
{
	GENERATED_BODY()

public:
	AChooseActConsole() = default;

	virtual void action(ABaseDrone* player) final;

	virtual ~AChooseActConsole() = default;
};
