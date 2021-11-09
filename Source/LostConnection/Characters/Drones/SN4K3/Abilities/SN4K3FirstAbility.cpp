#include "SN4K3FirstAbility.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Utility/InitUtility.h"
#include "SN4K3PassiveAbility.h"

void USN4K3FirstAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3FirstAbility, damage);

	DOREPLIFETIME(USN4K3FirstAbility, distance);
}

USN4K3FirstAbility::USN4K3FirstAbility() : 
	damage(375.0f),
	distance(1200.0f)
{
	cost = 90.0f;

	InitUtility::initAbilityId(__FILE__, id);
}

void USN4K3FirstAbility::applyAbility(ABaseCharacter* target)
{
	target->takeDamage(damage);

	ICaster::Execute_applyFirstAbilityEvent(Cast<UObject>(caster), target);
}

void USN4K3FirstAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(caster);
	UCapsuleComponent* capsule = drone->GetCapsuleComponent();
	UCameraComponent* camera = drone->GetFollowCamera();
	bool isFalling = drone->GetMovementComponent()->IsFalling();

	capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	if ((camera->GetComponentRotation().Pitch > 15.0f && !isFalling) || isFalling)
	{
		drone->AddActorWorldOffset(camera->GetComponentRotation().Vector() * distance, true);
	}
	else
	{
		FVector tem = camera->GetComponentRotation().Vector();

		tem.Z = 0.0f;

		drone->AddActorWorldOffset(tem * distance, true);
	}

	capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	Cast<USN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}
