#include "SN4K3FirstAbility.h"

#include "GameFramework/PawnMovementComponent.h"

#include "Characters/Drones/SN4K3/SN4K3.h"

ASN4K3FirstAbility::ASN4K3FirstAbility()
{

}

void ASN4K3FirstAbility::applyAbility(ABaseCharacter* target)
{

}

void ASN4K3FirstAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(owner);

	drone->GetMovementComponent()->Velocity += drone->GetFollowCamera()->GetComponentRotation().Vector() * 10000;

	drone->GetCapsuleComponent();
}
