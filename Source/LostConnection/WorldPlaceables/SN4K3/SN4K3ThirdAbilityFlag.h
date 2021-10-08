// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"

#include "WorldPlaceables/DroppedObject.h"
#include "Characters/Drones/SN4K3/Abilities/SN4K3ThirdAbility.h"

#include "SN4K3ThirdAbilityFlag.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ASN4K3ThirdAbilityFlag : public ADroppedObject
{
	GENERATED_BODY()

private:
	ASN4K3ThirdAbility* ability;
	TSet<AActor*> targets;
	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;

	float lifeTime;
	float currentTime;
	float period;
	float radius;

private:
	void Tick(float DeltaTime) override;
	
public:
	ASN4K3ThirdAbilityFlag();

	void setLifeTime(float lifeTime);

	void setAbility(ASN4K3ThirdAbility* ability);

	void setPeriod(float period);

	void setRadius(float radius);

	~ASN4K3ThirdAbilityFlag() = default;
};
