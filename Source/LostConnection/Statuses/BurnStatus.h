#pragma once

#include "CoreMinimal.h"

#include "BaseTickStatus.h"

#include "BurnStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UBurnStatus : public UBaseTickStatus
{
	GENERATED_BODY()
	
private:
	virtual FString getStatusName() const final override;

private:
	UPROPERTY(Category = Burn, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damage;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBurnStatus() = default;

	virtual void applyEffect(class IStatusReceiver* target, const FHitResult& hit) final override;

	virtual ~UBurnStatus() = default;
};
