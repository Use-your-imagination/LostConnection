#pragma once

#include "CoreMinimal.h"

#include "BaseTriggerStatus.h"

#include "ShatterStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UShatterStatus : public UBaseTriggerStatus
{
	GENERATED_BODY()
	
private:
	virtual FString getStatusName() const final override;

private:
	UPROPERTY(Category = Shatter, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float reservedDamage;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UShatterStatus() = default;

	void applyEffect(class IStatusReceiver* target, const FHitResult& hit) override;

	virtual ~UShatterStatus() = default;
};
