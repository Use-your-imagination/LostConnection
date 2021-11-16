#include "ShatterStatus.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"
#include "Characters/BaseCharacter.h"

FString UShatterStatus::getStatusName() const
{
	return "Shatter";
}

void UShatterStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UShatterStatus, reservedDamage);
}

void UShatterStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	Super::applyEffect(target, hit);

	ABaseCharacter* character = Cast<ABaseCharacter>(target);

	character->takeDamage(reservedDamage);
}
