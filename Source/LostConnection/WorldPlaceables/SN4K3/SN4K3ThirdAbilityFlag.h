// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "WorldPlaceables/DroppedObject.h"

#include "SN4K3ThirdAbilityFlag.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ASN4K3ThirdAbilityFlag : public ADroppedObject
{
	GENERATED_BODY()

private:
	float lifeTime;

private:
	void Tick(float DeltaTime) override;
	
public:
	ASN4K3ThirdAbilityFlag();

	~ASN4K3ThirdAbilityFlag() = default;
};
