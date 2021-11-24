// Copyright (c) 2021 Use-your-imagination

#include "ArcingCurrentStatus.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Characters/BaseCharacter.h"
#include "Interfaces/Gameplay/Descriptions/Derived/StatusReceiver.h"
#include "Utility/Utility.h"

FString UArcingCurrentStatus::getStatusName() const
{
	return "ArcingCurrent";
}

int32 UArcingCurrentStatus::calculateUnderStatusEffect() const
{
	return damageConversion * underStatusValueConversionCoefficient;
}

void UArcingCurrentStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UArcingCurrentStatus, damageConvertPercent);

	DOREPLIFETIME(UArcingCurrentStatus, damageConvertPercentPerTotalLifePercentPool);

	DOREPLIFETIME(UArcingCurrentStatus, radius);

	DOREPLIFETIME(UArcingCurrentStatus, underStatusValueConversionCoefficient);

	DOREPLIFETIME(UArcingCurrentStatus, damageConversion);
}

void UArcingCurrentStatus::increaseDamageConversion(IDamageInflictor* inflictor)
{
	damageConversion += target->getTotalLifePercentDealt(inflictor) * damageConvertPercentPerTotalLifePercentPool;
}

void UArcingCurrentStatus::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (Utility::isTargetAlreadyUnderStatus<UArcingCurrentStatus>(target))
	{
		const TArray<UBaseStatus*>& statuses = target->getStatuses();

		for (const auto& status : statuses)
		{
			UArcingCurrentStatus* arcing = Cast<UArcingCurrentStatus>(status);

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

	this->applyEffect(StaticCast<IStatusReceiver*>(target.GetInterface()), hit);
}

bool UArcingCurrentStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
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

float UArcingCurrentStatus::getInflictorDamage() const
{
	return inflictorDamage * (damageConversion / 100.0f);
}
