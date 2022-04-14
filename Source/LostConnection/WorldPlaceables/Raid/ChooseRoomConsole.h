// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Interfaces/Gameplay/Descriptions/Actionable.h"
#include "Characters/BaseDrone.h"

#include "ChooseRoomConsole.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API AChooseRoomConsole :
	public AActor,
	public IActionable
{
	GENERATED_BODY()
	
public:	
	AChooseRoomConsole() = default;

	void action(TObjectPtr<ABaseDrone> player);

	virtual ~AChooseRoomConsole() = default;
};
