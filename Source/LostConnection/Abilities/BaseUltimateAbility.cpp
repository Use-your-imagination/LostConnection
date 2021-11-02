#include "BaseUltimateAbility.h"

#include "Characters/BaseCharacter.h"

void UBaseUltimateAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseUltimateAbility, cooldown);

	DOREPLIFETIME(UBaseUltimateAbility, currentCooldown);
}

UBaseUltimateAbility::UBaseUltimateAbility()
{

}

float UBaseUltimateAbility::getCooldown() const
{
	return cooldown;
}

float UBaseUltimateAbility::getCurrentCooldown() const
{
	return currentCooldown;
}

void UBaseUltimateAbility::applyAbility(ABaseCharacter* target)
{
	PURE_VIRTUAL(UBaseUltimateAbility::applyAbility)
}

void UBaseUltimateAbility::useAbility()
{
	currentCooldown = cooldown;
}

void UBaseUltimateAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentCooldown > 0.0f)
	{
		currentCooldown -= DeltaTime;

		if (currentCooldown < 0.0f)
		{
			currentCooldown = 0.0f;
		}
	}
}
