#include "SN4K3SecondAbility.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "SN4K3PassiveAbility.h"

ASN4K3SecondAbility::ASN4K3SecondAbility()
{

}

void ASN4K3SecondAbility::applyAbility(ABaseCharacter* target)
{
	ICaster::Execute_applySecondAbilityEvent(Cast<UObject>(owner), target);
}

void ASN4K3SecondAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(owner);
	FHitResult hit;
	UWorld* world = drone->GetWorld();
	ABaseCharacter* target = nullptr;

	world->LineTraceSingleByChannel(hit, drone->getStartActionLineTrace(), drone->getEndActionLineTrace() + (5000.0f * drone->GetFollowCamera()->GetForwardVector()), ECollisionChannel::ECC_Visibility);

	target = Cast<ABaseCharacter>(hit.Actor);

	if (!target || target->getIsAlly())
	{
		return;
	}

	this->applyAbility(target);

	Cast<ASN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}
