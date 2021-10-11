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

void UBaseUltimateAbility::applyAbility(ABaseCharacter* target)
{
	PURE_VIRTUAL(UBaseUltimateAbility::applyAbility)
}

void UBaseUltimateAbility::useAbility()
{
	if (!currentCooldown)
	{
		return;
	}

	currentCooldown = cooldown;
}

void UBaseUltimateAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentCooldown -= DeltaTime;

	if (currentCooldown < 0.0f)
	{
		currentCooldown = 0.0f;
	}
}
