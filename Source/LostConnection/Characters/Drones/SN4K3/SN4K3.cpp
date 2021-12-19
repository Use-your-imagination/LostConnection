// Copyright (c) 2021 Use-your-imagination

#include "SN4K3.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "Abilities/SN4K3PassiveAbility.h"
#include "Abilities/SN4K3FirstAbility.h"
#include "Abilities/SN4K3SecondAbility.h"
#include "Abilities/SN4K3ThirdAbility.h"
#include "Abilities/SN4K3UltimateAbility.h"
#include "WorldPlaceables/SN4K3/SN4K3UltimateAbilityPlaceholder.h"
#include "Utility/MultiplayerUtility.h"
#include "Utility/Utility.h"
#include "AssetLoading/LostConnectionAssetManager.h"

void ASN4K3::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASN4K3, thirdAbilityReservator);
}

bool ASN4K3::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(thirdAbilityReservator, *Bunch, *RepFlags);

	return wroteSomething;
}

void ASN4K3::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		thirdAbilityReservator = NewObject<USN4K3Reservator>(this, ULostConnectionAssetManager::get().getStatuses().getDefaultSN4K3Reservator());

		Cast<USN4K3ThirdAbility>(thirdAbility)->insert(thirdAbilityReservator);
	}
}

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
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(this);
	const USN4K3DataAsset* data = Utility::findDroneAsset<USN4K3DataAsset>(ULostConnectionAssetManager::get().getDrones());
	UUserWidget* headUI = NewObject<UUserWidget>(playerState, data->getHeadUI());

	playerState->getCurrentUI()->RemoveFromViewport();

	playerState->setCurrentUI(headUI)->AddToViewport();

	passiveAbility->useAbility();

	// Destroy();
}

ASN4K3::ASN4K3()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASN4K3::onBeginOverlap);

	passiveAbility = CreateDefaultSubobject<USN4K3PassiveAbility>(TEXT("PassiveAbility"));
	firstAbility = CreateDefaultSubobject<USN4K3FirstAbility>(TEXT("FirstAbility"));
	secondAbility = CreateDefaultSubobject<USN4K3SecondAbility>(TEXT("SecondAbility"));
	thirdAbility = CreateDefaultSubobject<USN4K3ThirdAbility>(TEXT("ThirdAbility"));
	ultimateAbility = CreateDefaultSubobject<USN4K3UltimateAbility>(TEXT("UltimateAbility"));

	passiveAbility->setCaster(this);
	firstAbility->setCaster(this);
	secondAbility->setCaster(this);
	thirdAbility->setCaster(this);
	ultimateAbility->setCaster(this);
}

void ASN4K3::playUltimateReturnAnimation()
{
	GetMesh()->GetAnimInstance()->Montage_Play(Cast<USN4K3UltimateAbility>(ultimateAbility)->getReturnAnimation(), Utility::fromPercent(this->getCastPoint()));
}

void ASN4K3::setUltimatePlaceholder(ASN4K3UltimateAbilityPlaceholder* ultimatePlaceholder)
{
	this->ultimatePlaceholder = ultimatePlaceholder;
}

const TWeakObjectPtr<ASN4K3UltimateAbilityPlaceholder>& ASN4K3::getUltimatePlaceholder() const
{
	return ultimatePlaceholder;
}

bool ASN4K3::checkSecondAbilityCast() const
{
	bool result = ABaseDrone::checkSecondAbilityCast();
	FHitResult hit;
	UWorld* world = this->GetWorld();
	ABaseCharacter* target = nullptr;
	USN4K3SecondAbility* ability = Cast<USN4K3SecondAbility>(secondAbility);
	FCollisionQueryParams ignoreParameters;

	ignoreParameters.AddIgnoredActor(this);

	world->LineTraceSingleByChannel(hit, this->getStartActionLineTrace(), this->getEndActionLineTrace() + (ability->getDistance() * this->GetFollowCamera()->GetForwardVector()), ECollisionChannel::ECC_Camera, ignoreParameters);

	target = Cast<ABaseCharacter>(hit.Actor);

	result &= target && !target->getIsAlly();

	if (result)
	{
		ability->initDeathEvent(target);
	}

	return result;
}

bool ASN4K3::checkThirdAbilityCast() const
{
	bool result = ABaseDrone::checkThirdAbilityCast();

	result &= thirdAbilityReservator && thirdAbilityReservator->IsValidLowLevelFast() && !Cast<USN4K3ThirdAbility>(thirdAbility)->getIsFlagExist();

	return result;
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

	return ABaseDrone::checkUltimateAbilityCast();
}
