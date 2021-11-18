#pragma once

#include "CoreMinimal.h"

#include "BaseImpactStatus.h"

#include "CritStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UCritStatus : public UBaseImpactStatus
{
	GENERATED_BODY()

private:
	virtual FString getStatusName() const final override;

	virtual SIZE_T getActiveStatusesCount() const final override;

private:
	UPROPERTY(Category = Crit, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageMultiplier;

	UPROPERTY(Category = Crit, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float multiplierPerStatus;

private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UCritStatus() = default;

	virtual bool applyEffect(class IStatusReceiver* target, const FHitResult& hit) final override;

	virtual ~UCritStatus() = default;
};
