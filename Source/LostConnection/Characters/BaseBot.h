// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseCharacter.h"

#include "BaseBot.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ABaseBot : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void deathLogic() override;

public:
	ABaseBot();

	virtual ~ABaseBot() = default;
};
