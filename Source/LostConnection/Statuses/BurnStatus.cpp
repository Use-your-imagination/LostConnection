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

	DOREPLIFETIME(UBurnStatus, damageToStacksCoefficient);

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
		float decreaseStacks = FMath::Min(this->calculateStacks(damage), stacks);

		target->takeStatusDamage(damagePerStack * decreaseStacks);

		if (decreaseStacks == stacks)
		{
			const_cast<TArray<UBaseStatus*>&>(target->getStatuses()).Remove(this);
		}
		else
		{
			this->decreaseStacks(damage);
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

float UBurnStatus::getDamageToStacksCoefficient() const
{
	return damageToStacksCoefficient;
}

float& UBurnStatus::getStacks()
{
	return stacks;
}

float UBurnStatus::getStacks() const
{
	return stacks;
}
