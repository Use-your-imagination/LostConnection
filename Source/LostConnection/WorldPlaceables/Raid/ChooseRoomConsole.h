// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Interfaces/Gameplay/Descriptions/Actionable.h"
#include "Characters/BaseDrone.h"

#include "ChooseRoomConsole.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API AChooseRoomConsole :
	public AActor,
	public IActionable
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> mesh;
	
protected:
	void action(TObjectPtr<ABaseDrone> player) override;

public:	
	AChooseRoomConsole();

	bool isEnable() const override;

	~AChooseRoomConsole() = default;
};
