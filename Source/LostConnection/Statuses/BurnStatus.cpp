#include "BurnStatus.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"
#include "Utility/Utility.h"

FString UBurnStatus::getStatusName() const
{
	return "Burn";
}

void UBurnStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBurnStatus, damageToDamagePerStackCoefficient);

	DOREPLIFETIME(UBurnStatus, damageToReduceStacksCoefficient);

	DOREPLIFETIME(UBurnStatus, damageToInitalStacksCoefficient);

	DOREPLIFETIME(UBurnStatus, damagePerStack);

	DOREPLIFETIME(UBurnStatus, stacks);

	DOREPLIFETIME(UBurnStatus, stacksPerTick);
}

void UBurnStatus::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	float damage = inflictor->getInflictorDamage();

	if (Utility::isTargetAlreadyUnderStatus<UBurnStatus>(target))
	{
		// TODO: calculate damage of remaining damage

		// TODO: deal damage

		// TODO: remove status if remaining damage <= 0
		{
			const_cast<TArray<UBaseStatus*>&>(target->getStatuses()).Remove(this);
		}
		// else
		{
			// TODO: deal damage, decrease remaining damage
		}
	}
	else
	{
		Super::applyStatus_Implementation(inflictor, target, hit);

		damagePerStack = damage * damageToDamagePerStackCoefficient;

		stacks = damage * damageToInitalStacksCoefficient;

		stacksPerTick = stacks / duration;
	}
}

bool UBurnStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	target->takeStatusDamage(damagePerStack * stacksPerTick);

	stacks -= stacksPerTick;

	if (stacks <= 0)
	{
		return false;
	}

	return true;
}
