// Copyright (c) 2021 Use-your-imagination

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

	DOREPLIFETIME(UArcingCurrentAilment, increasedDamageCoefficients);

	DOREPLIFETIME(UArcingCurrentAilment, moreDamageCoefficients);
}

void UArcingCurrentAilment::increaseDamageConversion(IDamageInflictor* inflictor)
{
	damageConversionPercent += target->getTotalLifePercentDealt(inflictor) * damageConvertPercentPerTotalLifePercentPool;
}

void UArcingCurrentAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!target->_getUObject()->Implements<UAilmentReceiver>())
	{
		return;
	}

	if (Utility::isTargetAlreadyUnderStatus<UArcingCurrentAilment>(target))
	{
		const TArray<UBaseStatus*>& statuses = target->getStatuses();

		for (const auto& status : statuses)
		{
			UArcingCurrentAilment* arcing = Cast<UArcingCurrentAilment>(status);

			if (arcing)
			{
				arcing->increaseDamageConversion(this);

				target->setUnderStatusIntVariable(this->getStatusCountKey(), this->calculateUnderStatusEffect());
			}
		}
	}
	else
	{
		Super::applyStatus_Implementation(inflictor, target, hit);
	}

	this->applyEffect(StaticCast<IAilmentReceiver*>(target.GetInterface()), hit);
}

bool UArcingCurrentAilment::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	static TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes = { UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };

	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	TArray<AActor*> targets;

	UKismetSystemLibrary::SphereOverlapActors(Cast<UObject>(target)->GetWorld(), target->getMeshComponent()->GetComponentLocation(), radius, traceObjectTypes, ABaseCharacter::StaticClass(), {}, targets);

	for (auto& i : targets)
	{
		Cast<ABaseCharacter>(i)->takeDamage(this);
	}

	return true;
}

void UArcingCurrentAilment::appendIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Add(coefficient);
}

void UArcingCurrentAilment::removeIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Remove(coefficient);
}

void UArcingCurrentAilment::appendMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Add(coefficient);
}

void UArcingCurrentAilment::removeMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Remove(coefficient);
}

void UArcingCurrentAilment::setBaseDamage_Implementation(float newDamage)
{
	inflictorDamage = newDamage;
}

void UArcingCurrentAilment::setAddedDamage_Implementation(float newAddedDamage)
{
	inflictorAddedDamage = newAddedDamage;
}

void UArcingCurrentAilment::setAdditionalDamage_Implementation(float newAdditionalDamage)
{
	inflictorAdditionalDamage = newAdditionalDamage;
}

float UArcingCurrentAilment::getBaseDamage() const
{
	return inflictorDamage * Utility::fromPercent(damageConversionPercent);
}

float UArcingCurrentAilment::getAddedDamage() const
{
	return inflictorAddedDamage;
}

float UArcingCurrentAilment::getAdditionalDamage() const
{
	return inflictorAdditionalDamage;
}

TArray<float> UArcingCurrentAilment::getIncreasedDamageCoefficients() const
{
	return increasedDamageCoefficients;
}

TArray<float> UArcingCurrentAilment::getMoreDamageCoefficients() const
{
	return moreDamageCoefficients;
}

typeOfDamage UArcingCurrentAilment::getAilmentDamageType() const
{
	return typeOfDamage::electricity;
}
