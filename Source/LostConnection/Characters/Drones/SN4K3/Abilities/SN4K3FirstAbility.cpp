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

	DOREPLIFETIME(USN4K3FirstAbility, addedDamage);

	DOREPLIFETIME(USN4K3FirstAbility, additionalDamage);
	
	DOREPLIFETIME(USN4K3FirstAbility, increasedDamageCoefficients);

	DOREPLIFETIME(USN4K3FirstAbility, moreDamageCoefficients);
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

	target->statusInflictorImpactAction(this, hit);

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

void USN4K3FirstAbility::appendIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Add(coefficient);
}

void USN4K3FirstAbility::removeIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Remove(coefficient);
}

void USN4K3FirstAbility::appendMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Add(coefficient);
}

void USN4K3FirstAbility::removeMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Remove(coefficient);
}

void USN4K3FirstAbility::setBaseDamage_Implementation(float newDamage)
{
	damage = newDamage;
}

void USN4K3FirstAbility::setAddedDamage_Implementation(float newAddedDamage)
{
	addedDamage = newAddedDamage;
}

void USN4K3FirstAbility::setAdditionalDamage_Implementation(float newAdditionalDamage)
{
	additionalDamage = newAdditionalDamage;
}

float USN4K3FirstAbility::getBaseDamage() const
{
	return damage;
}

float USN4K3FirstAbility::getAddedDamage() const
{
	return addedDamage;
}

float USN4K3FirstAbility::getAdditionalDamage() const
{
	return additionalDamage;
}

TArray<float> USN4K3FirstAbility::getIncreasedDamageCoefficients() const
{
	return increasedDamageCoefficients;
}

TArray<float> USN4K3FirstAbility::getMoreDamageCoefficients() const
{
	return moreDamageCoefficients;
}

typeOfDamage USN4K3FirstAbility::getDamageType() const
{
	return typeOfDamage::nanite;
}

float USN4K3FirstAbility::getCrushingHitChance() const
{
	return Cast<USN4K3PassiveAbility>(Cast<ASN4K3>(caster)->getPassiveAbility())->getNaniteMeter();
}

float USN4K3FirstAbility::getAdditionalCrushingHitChance() const
{
	return 0.0f;
}
