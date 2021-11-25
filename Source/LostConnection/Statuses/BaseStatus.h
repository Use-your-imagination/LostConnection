// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "Net/UnrealNetwork.h"
#include "NiagaraSystem.h"

#include "Interfaces/Gameplay/Descriptions/Derived/AilmentInflictor.h"

#include "BaseStatus.generated.h"

#pragma warning(disable: 4458)

UENUM(BlueprintType)
enum class typeOfDamage : uint8
{
	none = 0 UMETA(DisplayName = "None"),
	physical = 1 UMETA(DisplayName = "Physical"),
	nanite = 2 UMETA(DisplayName = "Nanite"),
	fire = 3 UMETA(DisplayName = "Fire"),
	electricity = 4 UMETA(DisplayName = "Electricity"),
	radiation = 5 UMETA(DisplayName = "Radiation")
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

	virtual int32 calculateUnderStatusEffect() const;

protected:
	UPROPERTY(Category = Statuses, EditDefaultsOnly, BlueprintReadOnly)
	FText name;

	UPROPERTY(Category = Statuses, EditDefaultsOnly, BlueprintReadOnly)
	FText description;

	UPROPERTY(Category = Statuses, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float duration;

	UPROPERTY(Category = Statuses, Replicated, BlueprintReadOnly)
	float currentDuration;

	class IAilmentReceiver* target;

	typeOfDamage inflictorDamageType;
	float inflictorDamage;

protected:
	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* onApplyStatus;

	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* onApplyEffect;

public:
	UBaseStatus() = default;

	UFUNCTION(Server, Reliable)
	virtual void applyStatus(const TScriptInterface<IAilmentInflictor>& inflictor, const TScriptInterface<class IAilmentReceiver>& target, const FHitResult& hit);

	virtual bool applyEffect(class IAilmentReceiver* target, const FHitResult& hit);

	virtual void postRemove();

	virtual bool Tick(float DeltaTime);

	virtual void refreshDuration() final;

	virtual UNiagaraSystem* getOnApplyStatus() final;

	virtual UNiagaraSystem* getOnApplyEffect() final;

	virtual ~UBaseStatus() = default;
};
