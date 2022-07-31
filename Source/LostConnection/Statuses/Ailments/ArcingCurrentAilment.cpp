// Copyright (c) 2021 Use Your Imagination

#include "ArcingCurrentAilment.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Characters/BaseCharacter.h"
#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Utility/Utility.h"

FString UArcingCurrentAilment::getStatusName() const
{
	return "ArcingCurrent";
}

int32 UArcingCurrentAilment::calculateUnderStatusEffect() const
{
	return damageConversionPercent * underStatusValueConversionCoefficient;
}

void UArcingCurrentAilment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UArcingCurrentAilment, damageConvertPercent);

	DOREPLIFETIME(UArcingCurrentAilment, damageConvertPercentPerTotalLifePercentPool);

	DOREPLIFETIME(UArcingCurrentAilment, radius);

	DOREPLIFETIME(UArcingCurrentAilment, underStatusValueConversionCoefficient);

	DOREPLIFETIME(UArcingCurrentAilment, damageConversionPercent);

	DOREPLIFETIME(UArcingCurrentAilment, damageInflictorUtility);
}

UArcingCurrentAilment::UArcingCurrentAilment()
{
	damageInflictorUtility = CreateDefaultSubobject<UDamageInflictorUtility>("DamageInflictorUtility");
}

void UArcingCurrentAilment::increaseDamageConversion()
{
	damageConversionPercent += target->getTotalLifePercentDealt(inflictor.GetObject()) * damageConvertPercentPerTotalLifePercentPool;
}

void UArcingCurrentAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!target->_getUObject()->Implements<UAilmentReceiver>())
	{
		return;
	}

	if (Utility::isTargetAlreadyUnderStatus<UArcingCurrentAilment>(target))
	{
		this->inflictor = inflictor;

		for (const auto& status : target->getStatuses())
		{
			if (TObjectPtr<UArcingCurrentAilment> arcing = Cast<UArcingCurrentAilment>(status))
			{
				arcing->increaseDamageConversion();

				target->setUnderStatusIntVariable(this->getStatusCountKey(), this->calculateUnderStatusEffect());
			}
		}
	}
	else
	{
		Super::applyStatus_Implementation(inflictor, target, hit);
	}

	damageInflictorUtility->getDamage().baseDamage = inflictor->calculateTotalDamage(target.GetObject()) * Utility::fromPercent(damageConversionPercent);

	this->applyEffect(target, hit);
}

bool UArcingCurrentAilment::applyEffect(const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	static TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes = { UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };

	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	TArray<TObjectPtr<AActor>> targets;

	UKismetSystemLibrary::SphereOverlapActors
	(
		Cast<AActor>(target),
		target->getMeshComponent()->GetComponentLocation(),
		radius,
		traceObjectTypes,
		ABaseCharacter::StaticClass(),
		{},
		targets
	);

	for (const TObjectPtr<AActor>& otherTarget : targets)
	{
		Cast<ABaseCharacter>(otherTarget)->takeDamageFromInflictor(this);
	}

	return true;
}

bool UArcingCurrentAilment::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(damageInflictorUtility, *Bunch, *RepFlags);

	wroteSomething |= damageInflictorUtility->ReplicateSubobjects(Channel, Bunch, RepFlags);

	return wroteSomething;
}

UDamageInflictorUtility* UArcingCurrentAilment::getDamageInflictorUtility() const
{
	return damageInflictorUtility;
}

ETypeOfDamage UArcingCurrentAilment::getAilmentDamageType() const
{
	return ETypeOfDamage::electricity;
}
