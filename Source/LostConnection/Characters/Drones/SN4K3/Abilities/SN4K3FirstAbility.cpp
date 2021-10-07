#include "SN4K3FirstAbility.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Characters/Drones/SN4K3/Abilities/SN4K3PassiveAbility.h"

ASN4K3FirstAbility::ASN4K3FirstAbility()
{
	cost = 90.0f;
}

void ASN4K3FirstAbility::applyAbility(ABaseCharacter* target)
{
	target->takeDamage(375.0f);
}

void ASN4K3FirstAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(owner);
	UCapsuleComponent* capsule = drone->GetCapsuleComponent();
	UCameraComponent* camera = drone->GetFollowCamera();
	bool isFalling = drone->GetMovementComponent()->IsFalling();

	capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	if ((camera->GetComponentRotation().Pitch > 15.0f && !isFalling) || isFalling)
	{
		drone->AddActorWorldOffset(camera->GetComponentRotation().Vector() * 1200.0f, true);
	}
	else
	{
		FVector tem = camera->GetComponentRotation().Vector();

		tem.Z = 0.0f;

		drone->AddActorWorldOffset(tem * 1200.0f, true);
	}

	capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	Cast<ASN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}
