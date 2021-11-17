#include "BurnStatus.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"
#include "Characters/BaseCharacter.h"

FString UBurnStatus::getStatusName() const
{
	return "Burn";
}

void UBurnStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBurnStatus, damage);
}

void UBurnStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	Super::applyEffect(target, hit);

	ABaseCharacter* character = Cast<ABaseCharacter>(target);

	character->takeDamage(damage);
}
