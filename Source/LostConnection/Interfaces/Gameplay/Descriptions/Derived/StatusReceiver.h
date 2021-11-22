#pragma once

#include "CoreMinimal.h"

#include "NiagaraComponent.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageReceiver.h"
#include "Statuses/BaseStatus.h"

#include "StatusReceiver.generated.h"

UINTERFACE(MinimalAPI)
class UStatusReceiver : public UDamageReceiver
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IStatusReceiver : public IDamageReceiver
{
	GENERATED_BODY()

public:
	IStatusReceiver() = default;

	virtual void spawnApplyStatus(UNiagaraSystem* applyStatusVFX, const FHitResult& hit) = 0;

	virtual void spawnApplyEffect(UNiagaraSystem* applyEffectVFX, const FHitResult& hit) = 0;

	virtual void addStatus(UBaseStatus* status) = 0;

	virtual void applySwarmStatus(class USwarmStatus* swarm) = 0;

	virtual void inflictorImpactAction(const TScriptInterface<class IStatusInflictor>& inflictor, const FHitResult& hit) = 0;

	virtual void setUnderStatusIntVariable(const FString& key, int32 value) = 0;

	virtual const TArray<UBaseStatus*>& getStatuses() const = 0;
};
