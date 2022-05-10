// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Interfaces/Gameplay/Descriptions/Actionable.h"
#include "Characters/BaseDrone.h"

#include "ChooseActConsole.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API AChooseActConsole :
	public AActor,
	public IActionable
{
	GENERATED_BODY()

protected:
	void action(TObjectPtr<ABaseDrone> player) override;

public:
	AChooseActConsole() = default;

	virtual ~AChooseActConsole() = default;
};
