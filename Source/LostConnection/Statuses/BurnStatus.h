#pragma once

#include "CoreMinimal.h"

#include "BaseTickStatus.h"

#include "BurnStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UBurnStatus : public UBaseTickStatus
{
	GENERATED_BODY()
	
private:
	FString getStatusName() const override;

private:
	UPROPERTY(Category = Burn, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damage;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBurnStatus() = default;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void setDamage(float newDamage);

	virtual void applyEffect(class IStatusReceiver* target, const FHitResult& hit) override;

	virtual ~UBurnStatus() = default;
};
