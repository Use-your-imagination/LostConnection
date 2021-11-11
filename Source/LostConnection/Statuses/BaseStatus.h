#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "NiagaraComponent.h"
#include "Net/UnrealNetwork.h"

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
	virtual bool IsSupportedForNetworking() const final override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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

	TWeakObjectPtr<class ABaseCharacter> causer;

protected:
	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* onApplyStatus;

	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* onApplyEffect;

	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* underStatus;

public:
	UBaseStatus() = default;

	UFUNCTION(Server, Reliable)
	virtual void applyStatus(class ABaseCharacter* causer, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit);

	virtual void applyEffect(class IStatusReceiver* target, const FHitResult& hit);

	virtual void removeStatus(class IStatusReceiver* target) final;

	virtual bool Tick(float DeltaTime);

	virtual ~UBaseStatus() = default;
};
