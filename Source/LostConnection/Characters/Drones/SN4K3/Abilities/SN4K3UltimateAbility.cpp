// Copyright (c) 2021 Use-your-imagination

#include "SN4K3UltimateAbility.h"

#include "Components/CapsuleComponent.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Utility/InitializationUtility.h"
#include "Engine/LostConnectionGameState.h"
#include "WorldPlaceables/SN4K3/SN4K3UltimateAbilityPlaceholder.h"
#include "SN4K3PassiveAbility.h"

void USN4K3UltimateAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3UltimateAbility, isUltimateAbilityUsed);

	DOREPLIFETIME(USN4K3UltimateAbility, abilityDuration);

	DOREPLIFETIME(USN4K3UltimateAbility, currentAbilityDuration);
}

USN4K3UltimateAbility::USN4K3UltimateAbility() :
	abilityDuration(15.0f),
	currentAbilityDuration(0.0f)
{
	cooldown = 60.0f;

	InitializationUtility::initAbilityId(__FILE__, id);
}

UAnimMontage* USN4K3UltimateAbility::getReturnAnimation() const
{
	return returnAnimation;
}

void USN4K3UltimateAbility::applyAbility(ABaseCharacter* target)
{
	ASN4K3* drone = Cast<ASN4K3>(target);
	ASN4K3UltimateAbilityPlaceholder* placeholder = drone->getUltimatePlaceholder();
	FVector returnPosition;

	drone->GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	drone->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	if (currentAbilityDuration >= abilityDuration)
	{
		returnPosition = drone->GetActorLocation();
	}
	else
	{
		returnPosition = placeholder->GetActorLocation();
	}

	currentAbilityDuration = 0.0f;

	drone->setUltimatePlaceholder(nullptr);

	placeholder->Destroy();

	drone->SetActorLocation(returnPosition);

	ICaster::Execute_applyUltimateAbilityEvent(Cast<UObject>(caster), target);
}

void USN4K3UltimateAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(caster);

	if (isUltimateAbilityUsed)
	{
		isUltimateAbilityUsed = false;

		this->applyAbility(drone);

		return;
	}
	else if (currentCooldown)
	{
		return;
	}

	FVector tem = drone->GetActorLocation();

	tem.Z += drone->GetMesh()->GetRelativeLocation().Z;

	drone->GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	drone->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	isUltimateAbilityUsed = true;

	currentCooldown = cooldown;

	ASN4K3UltimateAbilityPlaceholder* placeholder = Utility::getGameState(drone)->spawn<ASN4K3UltimateAbilityPlaceholder>(FTransform(drone->GetMesh()->GetComponentRotation(), std::move(tem)));

	placeholder->setAbility(this);

	placeholder->FinishSpawning({}, true);

	drone->setUltimatePlaceholder(placeholder);

	Cast<USN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}

void USN4K3UltimateAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ASN4K3* drone = Cast<ASN4K3>(caster);

	if (isUltimateAbilityUsed)
	{
		currentAbilityDuration += DeltaTime;

		if (currentAbilityDuration >= abilityDuration)
		{
			isUltimateAbilityUsed = false;

			this->applyAbility(drone);
		}
	}
}
