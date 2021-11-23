// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseTickStatus.h"
#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

#include "BurnStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UBurnStatus :
	public UBaseTickStatus,
	public IDamageInflictor
{
	GENERATED_BODY()
	
private:
	virtual FString getStatusName() const final override;

private:
	UPROPERTY(Category = Burn, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float burnDamageCoefficient;

	UPROPERTY(Category = Burn, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float additionalFireCrushingHitChance;

	UPROPERTY(Category = Burn, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damage;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBurnStatus() = default;

	virtual float getAdditionalFireCrushingHitChance() const final;

	virtual void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) final override;

	virtual bool applyEffect(class IStatusReceiver* target, const FHitResult& hit) final override;

	virtual float getInflictorDamage() const final override;

	virtual ~UBurnStatus() = default;
};
