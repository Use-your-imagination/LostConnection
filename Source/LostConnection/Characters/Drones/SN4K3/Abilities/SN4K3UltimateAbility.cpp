// Copyright (c) 2021 Use-your-imagination

#include "SN4K3UltimateAbility.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

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

void USN4K3UltimateAbility::setCollisionResponseToPawnChannel(ABaseCharacter* target, ECollisionResponse response)
{
	target->GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, response);

	target->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, response);
}

USN4K3UltimateAbility::USN4K3UltimateAbility()
{
	InitializationUtility::initAbilityId(__FILE__, id);
}

UAnimMontage* USN4K3UltimateAbility::getReturnAnimation() const
{
	return returnAnimation;
}

float USN4K3UltimateAbility::getAbilityDuration() const
{
	return abilityDuration;
}

float USN4K3UltimateAbility::getCurrentAbilityDuration() const
{
	return currentAbilityDuration;
}

const TWeakObjectPtr<ASN4K3UltimateAbilityPlaceholder>& USN4K3UltimateAbility::getUltimatePlaceholder() const
{
	return ultimatePlaceholder;
}

void USN4K3UltimateAbility::applyAbility(ABaseCharacter* target)
{
	ASN4K3* drone = Cast<ASN4K3>(target);
	FVector returnPosition;

	this->setCollisionResponseToPawnChannel(drone, ECollisionResponse::ECR_Block);

	if (currentAbilityDuration >= abilityDuration)
	{
		returnPosition = drone->GetActorLocation();
	}
	else
	{
		returnPosition = ultimatePlaceholderLocation;

		ultimatePlaceholderLocation = FVector::ZeroVector;
	}

	currentAbilityDuration = 0.0f;

	if (ultimatePlaceholder.IsValid())
	{
		ultimatePlaceholder->Destroy();

		ultimatePlaceholderLocation = FVector::ZeroVector;
	}

	ultimatePlaceholder = nullptr;

	drone->SetActorLocation(returnPosition);

	isUltimateAbilityUsed = !isUltimateAbilityUsed;

	ICaster::Execute_applyUltimateAbilityEvent(Cast<UObject>(caster), target);
}

void USN4K3UltimateAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(caster);

	if (isUltimateAbilityUsed)
	{
		drone->restoreEnergy(cost);

		this->applyAbility(drone);

		return;
	}
	else if (currentCooldown)
	{
		return;
	}

	FVector tem = drone->GetActorLocation();
	const USN4K3DataAsset* data = Utility::findDroneAsset<USN4K3DataAsset>(ULostConnectionAssetManager::get().getDrones());

	tem.Z += drone->GetMesh()->GetRelativeLocation().Z;

	this->setCollisionResponseToPawnChannel(drone, ECollisionResponse::ECR_Ignore);

	isUltimateAbilityUsed = true;

	currentCooldown = cooldown;

	ASN4K3UltimateAbilityPlaceholder* placeholder = Utility::getGameState(drone)->spawn<ASN4K3UltimateAbilityPlaceholder>(data->getUltimateAbilityPlaceholder(), FTransform(drone->GetMesh()->GetComponentRotation(), MoveTemp(tem)));

	placeholder->setAbility(this);

	UGameplayStatics::FinishSpawningActor(placeholder, placeholder->GetActorTransform());

	ultimatePlaceholderLocation = placeholder->GetActorLocation();

	ultimatePlaceholder = placeholder;

	Cast<USN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}

void USN4K3UltimateAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isUltimateAbilityUsed)
	{
		currentAbilityDuration += DeltaTime;

		if (currentAbilityDuration >= abilityDuration)
		{
			this->applyAbility(Cast<ASN4K3>(caster));
		}
	}
}
