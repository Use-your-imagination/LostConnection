// Copyright (c) 2022 Use-your-imagination

#include "ShatterAilment.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Utility/Utility.h"

FString UShatterAilment::getStatusName() const
{
	return "Shatter";
}

int32 UShatterAilment::calculateUnderStatusEffect() const
{
	return FMath::CeilToInt(duration * 2.0f);
}

void UShatterAilment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UShatterAilment, durationConversionPercent);

	DOREPLIFETIME(UShatterAilment, damagePercentPerMeter);

	DOREPLIFETIME(UShatterAilment, damageInflictorUtility);
}

UShatterAilment::UShatterAilment()
{
	damageInflictorUtility = CreateDefaultSubobject<UDamageInflictorUtility>("DamageInflictorUtility");
}

void UShatterAilment::updateDuration(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target)
{
	duration += target->getTotalLifePercentDealt(inflictor) / Utility::fromPercent(durationConversionPercent);
}

void UShatterAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!target->_getUObject()->Implements<UAilmentReceiver>())
	{
		return;
	}

	if (!Utility::isTargetAlreadyUnderStatus<UShatterAilment>(target))
	{
		Super::applyStatus_Implementation(inflictor, target, hit);

		previousLocation = Cast<AActor>(target.GetObject())->GetActorLocation();
	}

	this->updateDuration(inflictor, target);
}

bool UShatterAilment::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	FVector currentTargetLocation = Cast<AActor>(target->_getUObject())->GetActorLocation();

	targetTotalLifePool = target->getTotalLifePool();

	damageInflictorUtility->setBaseDamage
	(
		targetTotalLifePool * Utility::fromPercent
		(
			(currentTargetLocation - previousLocation).Size() / 100.0f *
			damagePercentPerMeter
		)
	);

	target->takeDamageFromInflictor(this);

	previousLocation = MoveTemp(currentTargetLocation);

	return true;
}

bool UShatterAilment::Tick(float DeltaTime)
{
	tickPeriod = DeltaTime;

	return Super::Tick(DeltaTime);
}

bool UShatterAilment::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(damageInflictorUtility, *Bunch, *RepFlags);

	wroteSomething |= damageInflictorUtility->ReplicateSubobjects(Channel, Bunch, RepFlags);

	return wroteSomething;
}

UDamageInflictorUtility* UShatterAilment::getDamageInflictorUtility() const
{
	return damageInflictorUtility;
}

ETypeOfDamage UShatterAilment::getAilmentDamageType() const
{
	return ETypeOfDamage::cold;
}
