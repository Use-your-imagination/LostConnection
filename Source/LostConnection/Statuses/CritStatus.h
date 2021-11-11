#pragma once

#include "CoreMinimal.h"

#include "BaseImpactStatus.h"

#include "CritStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UCritStatus : public UBaseImpactStatus
{
	GENERATED_BODY()

private:
	float weaponDamage;
	
public:
	UCritStatus() = default;

	void applyEffect(class IStatusReceiver* target, const FHitResult& hit) override;

	virtual ~UCritStatus() = default;
};
