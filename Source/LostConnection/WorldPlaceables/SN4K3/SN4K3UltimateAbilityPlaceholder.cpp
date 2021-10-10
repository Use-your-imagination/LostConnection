#include "SN4K3UltimateAbilityPlaceholder.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Ammo/BaseAmmo.h"

ASN4K3UltimateAbilityPlaceholder::ASN4K3UltimateAbilityPlaceholder()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshFinder(TEXT("SkeletalMesh'/Game/Assets/Characters/Drone/Drone.Drone'"));

	mesh->SetSkeletalMesh(meshFinder.Object);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	mesh->SetGenerateOverlapEvents(true);

	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
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

void ASN4K3UltimateAbilityPlaceholder::impactAction_Implementation(ABaseAmmo* ammo)
{
	ASN4K3* drone = Cast<ASN4K3>(ability->getOwnerCaster());

	if (drone->getIsAlly() == ammo->getIsAlly())
	{
		return;
	}

	ability->applyAbility(drone);
}
