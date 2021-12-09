// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"
#include "Interfaces/Gameplay/Statuses/Buff.h"

#include "SN4K3ReservatorBuff.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3ReservatorBuff :
	public UBaseStatus,
	public IBuff
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float healthReservePercent;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float naniteAdditionalDamagePercent;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float reservedHealth;

	TMap<TWeakObjectPtr<UObject>, FSimpleDelegate> additionalNaniteDamage;

private:
	virtual FString getStatusName() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USN4K3ReservatorBuff();

	void setHealthReservePercent(float healthReservePercent);

	void setNaniteAdditionalDamagePercent(float naniteAdditionalDamagePercent);

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	bool applyEffect(IStatusReceiver* target, const FHitResult& hit) override;

	void postRemove() override;

	virtual ~USN4K3ReservatorBuff() = default;
};
