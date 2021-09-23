#include "BaseAbility.h"

#include "Characters/BaseCharacter.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

#pragma warning(disable: 4458)

void ABaseAbility::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseAbility, cost);

	DOREPLIFETIME(ABaseAbility, isDisabled);
}

ABaseAbility::ABaseAbility()
{
	PrimaryActorTick.bCanEverTick = true;
	NetUpdateFrequency = 1;
}

void ABaseAbility::applyAbility(ABaseCharacter* target)
{
	PURE_VIRTUAL(ABaseAbility::applyAbility);
}

void ABaseAbility::useAbility()
{
	PURE_VIRTUAL(ABaseAbility::useAbility);
}

void ABaseAbility::setCost_Implementation(float newCost)
{
	cost = newCost;
}

void ABaseAbility::setOwner(ICaster* owner)
{
	this->owner = owner;
}

void ABaseAbility::disable_Implementation()
{
	isDisabled = true;
}

void ABaseAbility::enable_Implementation()
{
	isDisabled = false;
}

float ABaseAbility::getCost() const
{
	return cost;
}

bool ABaseAbility::getIsDisabled() const
{
	return isDisabled;
}

const FString& ABaseAbility::getLocalizedName() const
{
	return localizedName;
}
