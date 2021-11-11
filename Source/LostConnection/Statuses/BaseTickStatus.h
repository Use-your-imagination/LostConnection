#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"

#include "BaseTickStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseTickStatus : public UBaseStatus
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = TickStatus, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float tickPeriod;

	UPROPERTY(Category = TickStatus, Replicated, BlueprintReadOnly)
	float currentTickPeriod;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UBaseTickStatus() = default;

	virtual void applyEffect(class IStatusReceiver* target, const FHitResult& hit) override;

	virtual bool Tick(float DeltaTime) override;

	virtual ~UBaseTickStatus() = default;
};
