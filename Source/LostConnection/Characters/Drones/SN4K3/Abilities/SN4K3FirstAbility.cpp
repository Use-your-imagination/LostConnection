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

void USN4K3FirstAbility::applyAbility(ABaseCharacter* target)
{
	FHitResult hit(target, target->getMeshComponent(), target->GetActorLocation(), {});

	ailmentInflictorUtility->setBaseCrushingHitChance(Cast<USN4K3PassiveAbility>(Cast<ASN4K3>(caster)->getPassiveAbility())->getNaniteMeter());

	// TODO: remake apply modules

	TObjectPtr<UAilmentInflictorUtility> tem = NewObject<UAilmentInflictorUtility>(nullptr);

	tem->setAddedDamage(ailmentInflictorUtility->getAddedDamage());
	tem->setAdditionalCrushingHitChance(ailmentInflictorUtility->getAdditionalCrushingHitChance());
	tem->setAdditionalDamage(ailmentInflictorUtility->getAdditionalDamage());
	tem->setBaseCrushingHitChance(ailmentInflictorUtility->getBaseCrushingHitChance());
	tem->setBaseDamage(ailmentInflictorUtility->getBaseDamage());
	
	for (float increaseCoefficient : ailmentInflictorUtility->getIncreaseDamageCoefficients())
	{
		tem->appendIncreaseDamageCoefficient(increaseCoefficient);
	}

	for (float moreCoefficient : ailmentInflictorUtility->getMoreDamageCoefficients())
	{
		tem->appendMoreDamageCoefficient(moreCoefficient);
	}

	if (IPersonalModulesHolder* holder = Cast<IPersonalModulesHolder>(caster))
	{
		Utility::applyDamageModules(Cast<AActor>(caster), holder->getPersonalEquippedModules(), tem);

		Utility::applyDamageModules(Cast<AActor>(caster), holder->getPersonalUnequippedModules(), tem);
	}

	if (IWeaponModulesHolder* holder = Cast<IWeaponModulesHolder>(caster))
	{
		Utility::applyDamageModules(Cast<AActor>(caster), holder->getWeaponModules(), tem);
	}

	target->takeDamageFromInflictor(tem.Get());

	target->statusInflictorImpactAction(tem.Get(), hit);

	ICaster::Execute_applyFirstAbilityEvent(Cast<UObject>(caster), target);
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
