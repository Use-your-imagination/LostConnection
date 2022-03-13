// Copyright (c) 2021 Use-your-imagination

#include "BaseAbility.h"

#include "Characters/BaseCharacter.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

#pragma warning(disable: 4458)

void UBaseAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseAbility, cost);

	DOREPLIFETIME(UBaseAbility, isDisabled);
}

UBaseAbility::UBaseAbility() :
	cancelBlendOutTime(0.25f)
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

void UBaseAbility::initAbility()
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

bool UBaseAbility::getIsGrounded() const
{
	return isGrounded;
}

float UBaseAbility::getCancelBlendOutTime() const
{
	return cancelBlendOutTime;
}

UAnimMontage* UBaseAbility::getAnimation()
{
	return animation;
}

EAbilitySlot UBaseAbility::getId() const
{
	return id;
}

ICaster* UBaseAbility::getCaster() const
{
	return caster;
}
