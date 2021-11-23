// Copyright (c) 2021 Use-your-imagination

#include "SN4K3FirstAbility.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Utility/InitializationUtility.h"
#include "Utility/Utility.h"
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

	InitializationUtility::initAbilityId(__FILE__, id);
}

void USN4K3FirstAbility::applyAbility(ABaseCharacter* target)
{
	FHitResult hit;

	hit.Actor = target;
	hit.Component = target->getMeshComponent();
	hit.Location = target->GetActorLocation();

	target->takeDamage(this);

	target->inflictorImpactAction(this, hit);

	ICaster::Execute_applyFirstAbilityEvent(Cast<UObject>(caster), target);
}

void USN4K3FirstAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(caster);
	UCapsuleComponent* capsule = drone->GetCapsuleComponent();
	UCameraComponent* camera = drone->GetFollowCamera();
	bool isFalling = drone->GetMovementComponent()->IsFalling();
	FVector offset = camera->GetComponentRotation().Vector();

	capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	if (!((camera->GetComponentRotation().Pitch > 15.0f && !isFalling) || isFalling))
	{
		offset.Z = 0.0f;
	}

	drone->AddActorWorldOffset(offset * distance, true);

	capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	Cast<USN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}

float USN4K3FirstAbility::getInflictorDamage() const
{
	return damage;
}

typeOfDamage USN4K3FirstAbility::getDamageType() const
{
	return typeOfDamage::nanite;
}

bool USN4K3FirstAbility::getCrushingHitProc() const
{
	return Utility::checkChanceProc(Cast<USN4K3PassiveAbility>(Cast<ASN4K3>(caster)->getPassiveAbility())->getNaniteMeter());
}
