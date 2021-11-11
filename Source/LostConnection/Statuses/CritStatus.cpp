#include "CritStatus.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"
#include "Characters/BaseCharacter.h"

void UCritStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, L"Crit");
}
