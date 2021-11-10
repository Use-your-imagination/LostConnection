#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"

#include "ShatterStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UShatterStatus : public UBaseStatus
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Shatter, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float reservedDamage;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UShatterStatus();

	void applyEffect(class IStatusReceiver* target) override;

	virtual ~UShatterStatus() = default;
};
