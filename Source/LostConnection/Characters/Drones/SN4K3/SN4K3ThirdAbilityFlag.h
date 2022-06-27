// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "WorldPlaceables/DroppedObject.h"
#include "Abilities/SN4K3ThirdAbility.h"

#include "SN4K3ThirdAbilityFlag.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API ASN4K3ThirdAbilityFlag : public ADroppedObject
{
	GENERATED_BODY()

private:
	USN4K3ThirdAbility* ability;
	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;

	float lifetime;
	float currentTime;
	float period;
	float radius;

private:
	void Tick(float DeltaTime) override;
	
public:
	ASN4K3ThirdAbilityFlag();

	void setLifetime(float lifetime);

	void setAbility(USN4K3ThirdAbility* ability);

	void setPeriod(float period);

	void setRadius(float radius);

	~ASN4K3ThirdAbilityFlag() = default;
};
