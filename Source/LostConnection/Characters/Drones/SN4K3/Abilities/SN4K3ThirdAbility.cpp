#include "SN4K3ThirdAbility.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "WorldPlaceables/SN4K3/SN4K3ThirdAbilityFlag.h"
#include "Engine/LostConnectionGameState.h"
#include "SN4K3PassiveAbility.h"

USN4K3ThirdAbility::USN4K3ThirdAbility()
{

}

void USN4K3ThirdAbility::applyAbility(ABaseCharacter* target)
{
	target->setHealth(target->getHealth() * 1.5);

	ICaster::Execute_applyThirdAbilityEvent(Cast<UObject>(caster), target);
}

void USN4K3ThirdAbility::removeAbilityEffect(ABaseCharacter* target)
{
	float health = target->getHealth();

	target->setHealth(health - health / 3);
}

void USN4K3ThirdAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(caster);
	FVector tem = drone->GetActorForwardVector() * 200;

	tem.Z += drone->GetMesh()->GetRelativeLocation().Z;

	ASN4K3ThirdAbilityFlag* flag = drone->GetWorld()->GetGameState<ALostConnectionGameState>()->spawn<ASN4K3ThirdAbilityFlag>({ drone->GetActorRotation(), tem + drone->GetActorLocation() });

	flag->setLifeTime(10.0f);

	flag->setRadius(350.0f);

	flag->setAbility(this);

	flag->setPeriod(1.0f);

	flag->FinishSpawning({}, true);

	Cast<USN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}
