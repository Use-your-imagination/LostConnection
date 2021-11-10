#include "ShatterStatus.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"
#include "Characters/BaseCharacter.h"

void UShatterStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UShatterStatus, reservedDamage);
}

void UShatterStatus::applyEffect(IStatusReceiver* target)
{
	ABaseCharacter* character = Cast<ABaseCharacter>(target);

	character->takeDamage(reservedDamage);
}
