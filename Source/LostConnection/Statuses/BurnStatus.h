#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"

#include "BurnStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UBurnStatus : public UBaseStatus
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Burn, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damage;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBurnStatus() = default;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void setDamage(float newDamage);

	virtual void applyEffect(class IStatusReceiver* target) override;

	virtual ~UBurnStatus() = default;
};
