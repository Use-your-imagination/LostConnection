#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "Net/UnrealNetwork.h"
#include "UObject/WeakInterfacePtr.h"
#include "NiagaraSystem.h"

#include "Interfaces/Gameplay/Descriptions/StatusInflictor.h"

#include "BaseStatus.generated.h"

#pragma warning(disable: 4458)

UENUM(BlueprintType)
enum class typeOfDamage : uint8
{
	none = 0 UMETA(DisplayName = "None"),
	physical = 1 UMETA(DisplayName = "Physical"),
	cold = 2 UMETA(DisplayName = "Cold"),
	nanite = 3 UMETA(DisplayName = "Nanite"),
	fire = 4 UMETA(DisplayName = "Fire"),
	electricity = 5 UMETA(DisplayName = "Electricity")
};

UCLASS(BlueprintType, Blueprintable, DefaultToInstanced)
class LOSTCONNECTION_API UBaseStatus : public UObject
{
	GENERATED_BODY()

protected:
	virtual FString getStatusCountKey() const final;

protected:
	virtual bool IsSupportedForNetworking() const final override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual FString getStatusName() const;

protected:
	UPROPERTY(Category = Statuses, EditDefaultsOnly, BlueprintReadOnly)
	FText name;

	UPROPERTY(Category = Statuses, EditDefaultsOnly, BlueprintReadOnly)
	FText description;

	UPROPERTY(Category = Statuses, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float duration;

	UPROPERTY(Category = Statuses, Replicated, BlueprintReadOnly)
	float currentDuration;

	class IStatusReceiver* target;

	TWeakInterfacePtr<IStatusInflictor> inflictor;

protected:
	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* onApplyStatus;

	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* onApplyEffect;

public:
	UBaseStatus() = default;

	UFUNCTION(Server, Reliable)
	virtual void applyStatus(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit);

	virtual void applyEffect(class IStatusReceiver* target, const FHitResult& hit);

	virtual void postRemove();

	virtual bool Tick(float DeltaTime);

	virtual UNiagaraSystem* getOnApplyStatus() final;

	virtual UNiagaraSystem* getOnApplyEffect() final;

	virtual ~UBaseStatus() = default;
};
