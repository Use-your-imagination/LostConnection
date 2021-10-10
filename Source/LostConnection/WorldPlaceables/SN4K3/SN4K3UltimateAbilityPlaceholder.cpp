#include "SN4K3UltimateAbilityPlaceholder.h"

#include "Characters/Drones/SN4K3/SN4K3.h"

ASN4K3UltimateAbilityPlaceholder::ASN4K3UltimateAbilityPlaceholder()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshFinder(TEXT("SkeletalMesh'/Game/Assets/Characters/Drone/Drone.Drone'"));

	mesh->SetSkeletalMesh(meshFinder.Object);
}

void ASN4K3UltimateAbilityPlaceholder::setAbility(ASN4K3UltimateAbility* ability)
{
	this->ability = ability;
}

float ASN4K3UltimateAbilityPlaceholder::getFlatDamageReduction_Implementation() const
{
	return 0.0f;
}

float ASN4K3UltimateAbilityPlaceholder::getPercentageDamageReduction_Implementation() const
{
	return 0.0;
}

void ASN4K3UltimateAbilityPlaceholder::impactAction_Implementation(class ABaseAmmo* ammo)
{
	ASN4K3* drone = Cast<ASN4K3>(ability->getOwnerCaster());

	ability->applyAbility(drone);
}
