// Copyright (c) 2021 Use Your Imagination

#include "SN4K3.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "Abilities/SN4K3PassiveAbility.h"
#include "Abilities/SN4K3FirstAbility.h"
#include "Abilities/SN4K3SecondAbility.h"
#include "Abilities/SN4K3ThirdAbility.h"
#include "Abilities/SN4K3UltimateAbility.h"
#include "SN4K3UltimateAbilityPlaceholder.h"
#include "Utility/MultiplayerUtility.h"
#include "Utility/Utility.h"
#include "AssetLoading/LostConnectionAssetManager.h"

void ASN4K3::onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* target = Cast<ABaseCharacter>(OtherActor);

	if (!target || isAlly == target->getIsAlly())
	{
		return;
	}

	firstAbility->applyAbility(target);
}

void ASN4K3::deathLogic()
{
	const TWeakObjectPtr<ASN4K3UltimateAbilityPlaceholder>& placeholder = Cast<USN4K3UltimateAbility>(ultimateAbility)->getUltimatePlaceholder();

	if (placeholder.IsValid())
	{
		placeholder->Destroy();
	}

	if (this->checkPassiveAbilityCast())
	{
		Cast<USN4K3PassiveAbility>(passiveAbility)->startCooldown();

		Super::deathLogic();

		passiveAbility->useAbility();

		Destroy();
	}
	else
	{
		isFullyDestruction = true;

		Super::deathLogic();
	}
}

ASN4K3::ASN4K3()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASN4K3::onBeginOverlap);

	passiveAbility = CreateDefaultSubobject<USN4K3PassiveAbility>("PassiveAbility");
	firstAbility = CreateDefaultSubobject<USN4K3FirstAbility>("FirstAbility");
	secondAbility = CreateDefaultSubobject<USN4K3SecondAbility>("SecondAbility");
	thirdAbility = CreateDefaultSubobject<USN4K3ThirdAbility>("ThirdAbility");
	ultimateAbility = CreateDefaultSubobject<USN4K3UltimateAbility>("UltimateAbility");

	passiveAbility->setCaster(this);
	firstAbility->setCaster(this);
	secondAbility->setCaster(this);
	thirdAbility->setCaster(this);
	ultimateAbility->setCaster(this);
}

void ASN4K3::playUltimateReturnAnimation()
{
	PlayAnimMontage(Cast<USN4K3UltimateAbility>(ultimateAbility)->getReturnAnimation(), Utility::fromPercent(this->getCastPoint()));
}

bool ASN4K3::checkPassiveAbilityCast() const
{
	if (!Super::checkPassiveAbilityCast())
	{
		return false;
	}

	return Cast<USN4K3PassiveAbility>(passiveAbility)->isUsable();
}

bool ASN4K3::checkSecondAbilityCast() const
{
	if (!Super::checkSecondAbilityCast())
	{
		return false;
	}

	bool result;
	FHitResult hit;
	UWorld* world = this->GetWorld();
	ABaseCharacter* target = nullptr;
	USN4K3SecondAbility* ability = Cast<USN4K3SecondAbility>(secondAbility);
	FCollisionQueryParams ignoreParameters;

	ignoreParameters.AddIgnoredActor(this);

	world->LineTraceSingleByChannel(hit, this->getStartActionLineTrace(), this->getEndActionLineTrace() + (ability->getDistance() * this->GetFollowCamera()->GetForwardVector()), ECollisionChannel::ECC_Camera, ignoreParameters);

	target = Cast<ABaseCharacter>(hit.GetActor());

	result = target && !target->getIsAlly();

	if (result)
	{
		ability->initDeathEvent(target);
	}

	return result;
}

bool ASN4K3::checkThirdAbilityCast() const
{
	if (!Super::checkThirdAbilityCast())
	{
		return false;
	}

	USN4K3ThirdAbility* ability = Cast<USN4K3ThirdAbility>(thirdAbility);

	return IsValid(ability);
}

bool ASN4K3::checkUltimateAbilityCast() const
{
	USN4K3UltimateAbility* ability = Cast<USN4K3UltimateAbility>(ultimateAbility);
	bool used = ability->getIsUltimateAbilityUsed();
	float castAnimationTime = ability->getReturnAnimation()->GetPlayLength() * Utility::fromPercent(this->getCastPoint());

	if (used && (ability->getCurrentAbilityDuration() + castAnimationTime < ability->getAbilityDuration()))
	{
		MultiplayerUtility::runOnServerReliableWithMulticast(const_cast<ASN4K3*>(this), "playUltimateReturnAnimation");

		return false;
	}

	return Super::checkUltimateAbilityCast();
}
