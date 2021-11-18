#pragma once

#include "CoreMinimal.h"

#include "BaseTickStatus.h"
#include "Interfaces/Gameplay/Descriptions/Stackable.h"

#include "BurnStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UBurnStatus : 
	public UBaseTickStatus,
	public IStackable
{
	GENERATED_BODY()
	
private:
	virtual FString getStatusName() const final override;

private:
	UPROPERTY(Category = Burn, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageToDamagePerStackCoefficient;
	
	UPROPERTY(Category = Burn, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageToReduceStacksCoefficient;

	UPROPERTY(Category = Burn, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageToInitalStacksCoefficient;

	UPROPERTY(Category = Burn, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damagePerStack;

	UPROPERTY(Category = Burn, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float stacks;

	UPROPERTY(Category = Burn, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float stacksPerTick;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBurnStatus() = default;

	virtual void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) final override;

	virtual bool applyEffect(class IStatusReceiver* target, const FHitResult& hit) final override;

	virtual float getDamageToStacksCoefficient() const final override;

	virtual float& getStacks() final override;

	virtual float getStacks() const final override;

	virtual ~UBurnStatus() = default;
};
