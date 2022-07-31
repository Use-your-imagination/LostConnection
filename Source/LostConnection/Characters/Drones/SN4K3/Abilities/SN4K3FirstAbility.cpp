// Copyright (c) 2021 Use Your Imagination

#include "SN4K3FirstAbility.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Utility/InitializationUtility.h"
#include "Utility/Utility.h"
#include "SN4K3PassiveAbility.h"
#include "Interfaces/Modules/Damage/DamageModule.h"
#include "Modules/Base/BaseModule.h"

void USN4K3FirstAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3FirstAbility, distance);

	DOREPLIFETIME(USN4K3FirstAbility, ailmentInflictorUtility);
}

USN4K3FirstAbility::USN4K3FirstAbility() :
	distance(1200.0f)
{
	cost = 90.0f;

	InitializationUtility::initAbilityId(__FILE__, id);
}

void USN4K3FirstAbility::initAbility(const TObjectPtr<AController>& instigator)
{
	Super::initAbility(instigator);

	ailmentInflictorUtility->setDamageInstigator(instigator);
}

void USN4K3FirstAbility::applyAbility(ABaseCharacter* target)
{
	FHitResult hit(target, target->getMeshComponent(), target->GetActorLocation(), {});

	ailmentInflictorUtility->setBaseCrushingHitChance(Cast<USN4K3PassiveAbility>(Cast<ASN4K3>(caster)->getPassiveAbility())->getNaniteMeter());

	target->statusInflictorImpactAction(ailmentInflictorUtility.Get(), hit);

	target->takeDamageFromInflictor(ailmentInflictorUtility.Get());

	ICaster::Execute_applyFirstAbilityEvent(caster.GetObject(), target);
}

void USN4K3FirstAbility::useAbility()
{
	TObjectPtr<ASN4K3> drone = Cast<ASN4K3>(caster);
	TObjectPtr<UCapsuleComponent> capsule = drone->GetCapsuleComponent();
	TObjectPtr<UCameraComponent> camera = drone->GetFollowCamera();
	bool isFalling = drone->GetMovementComponent()->IsFalling();
	FVector offset = camera->GetComponentRotation().Vector();

	capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	if (!((camera->GetComponentRotation().Pitch > 15.0f && !isFalling) || isFalling))
	{
		offset.Z = 0.0f;
	}

	drone->AddActorWorldOffset(offset * distance, true, nullptr, ETeleportType::TeleportPhysics);

	capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	Cast<USN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}

bool USN4K3FirstAbility::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(ailmentInflictorUtility, *Bunch, *RepFlags);

	wroteSomething |= ailmentInflictorUtility->ReplicateSubobjects(Channel, Bunch, RepFlags);

	return wroteSomething;
}

UAilmentInflictorUtility* USN4K3FirstAbility::getAilmentInflictorUtility() const
{
	return ailmentInflictorUtility;
}
