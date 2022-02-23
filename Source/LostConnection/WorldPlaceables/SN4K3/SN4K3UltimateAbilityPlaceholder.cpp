// Copyright (c) 2021 Use-your-imagination

#include "SN4K3UltimateAbilityPlaceholder.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Constants/Constants.h"
#include "Projectiles/Ammo.h"

ASN4K3UltimateAbilityPlaceholder::ASN4K3UltimateAbilityPlaceholder()
{
	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	mesh->SetGenerateOverlapEvents(true);

	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	mesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
}

void ASN4K3UltimateAbilityPlaceholder::setAbility(USN4K3UltimateAbility* ability)
{
	this->ability = ability;
}

void ASN4K3UltimateAbilityPlaceholder::impactAction_Implementation(AAmmo* ammo, const FHitResult& hit)
{
	ASN4K3* drone = Cast<ASN4K3>(ability->getCaster());

	if (drone->getIsAlly() == ammo->getIsAlly())
	{
		return;
	}

	ability->applyAbility(drone);
}

float ASN4K3UltimateAbilityPlaceholder::getFlatDamageReduction_Implementation() const
{
	return 0.0f;
}

float ASN4K3UltimateAbilityPlaceholder::getPercentageDamageReduction_Implementation() const
{
	return 10.0;
}
