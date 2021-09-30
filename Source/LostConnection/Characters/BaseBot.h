// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseDrone.h"

#include "BaseBot.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ABaseBot : public ABaseDrone
{
	GENERATED_BODY()

private:
	bool isReadyForDestroy;

protected:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void deathLogic() override;

public:
	ABaseBot();

	virtual ~ABaseBot() = default;
};
