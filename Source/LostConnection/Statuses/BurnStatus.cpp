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

	DOREPLIFETIME(UBurnStatus, burnDamageCoefficient);

	DOREPLIFETIME(UBurnStatus, additionalFireCrushingHitChance);

	DOREPLIFETIME(UBurnStatus, damage);
}

void UBurnStatus::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	Super::applyStatus_Implementation(inflictor, target, hit);

	damage = (inflictorDamage * burnDamageCoefficient) / (duration / tickPeriod);
}

bool UBurnStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	target->takeStatusDamage(damage);

	return true;
}
