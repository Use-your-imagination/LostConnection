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

bool UShatterStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	ABaseCharacter* character = Cast<ABaseCharacter>(target);

	character->takeDamage(reservedDamage);

	return true;
}
