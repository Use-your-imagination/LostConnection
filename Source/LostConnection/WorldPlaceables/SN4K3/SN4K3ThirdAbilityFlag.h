#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"

#include "WorldPlaceables/DroppedObject.h"
#include "Characters/Drones/SN4K3/Abilities/SN4K3ThirdAbility.h"

#include "SN4K3ThirdAbilityFlag.generated.h"

UCLASS()
class LOSTCONNECTION_API ASN4K3ThirdAbilityFlag : public ADroppedObject
{
	GENERATED_BODY()

private:
	USN4K3ThirdAbility* ability;
	TSet<AActor*> targets;
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
