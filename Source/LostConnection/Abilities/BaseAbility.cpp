#include "BaseAbility.h"

#include "Characters/BaseCharacter.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

#pragma warning(disable: 4458)

bool UBaseAbility::IsSupportedForNetworking() const
{
	return true;
}

void UBaseAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseAbility, cost);

	DOREPLIFETIME(UBaseAbility, isDisabled);
}

UBaseAbility::UBaseAbility()
{
	
}

void UBaseAbility::applyAbility(ABaseCharacter* target)
{
	PURE_VIRTUAL(UBaseAbility::applyAbility);
}

void UBaseAbility::useAbility()
{
	PURE_VIRTUAL(UBaseAbility::useAbility);
}

void UBaseAbility::Tick(float DeltaTime)
{

}

void UBaseAbility::setCost_Implementation(float newCost)
{
	cost = newCost;
}

void UBaseAbility::setCaster(ICaster* caster)
{
	this->caster = caster;
}

void UBaseAbility::disable_Implementation()
{
	isDisabled = true;
}

void UBaseAbility::enable_Implementation()
{
	isDisabled = false;
}

float UBaseAbility::getCost() const
{
	return cost;
}

bool UBaseAbility::getIsDisabled() const
{
	return isDisabled;
}

const FText& UBaseAbility::getName() const
{
	return name;
}

const FText& UBaseAbility::getDescription() const
{
	return description;
}

bool UBaseAbility::getIsCancelable() const
{
	return isCancelable;
}

ICaster* UBaseAbility::getCaster()
{
	return caster;
}
