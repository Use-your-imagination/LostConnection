// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Info.h"
#include "Components/ArrowComponent.h"

#include "Utility/Enums.h"

#include "AISpawnPoint.generated.h"

UCLASS(Blueprintable)
class LOSTCONNECTION_API AAISpawnPoint : public AInfo
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Components, VisibleAnywhere, Meta = (AllowPrivateAccess))
	TObjectPtr<UArrowComponent> arrow;

	UPROPERTY(Category = Waves, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	EBotType botSpawnType;

public:
	AAISpawnPoint();

	EBotType getBotSpawnType() const;

	~AAISpawnPoint() = default;
};
