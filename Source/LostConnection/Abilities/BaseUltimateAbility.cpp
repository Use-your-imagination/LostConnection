#include "BaseUltimateAbility.h"

#include "Characters/BaseCharacter.h"

void ABaseUltimateAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority() && currentCooldown > 0.0f)
	{
		currentCooldown -= DeltaTime;

		if (currentCooldown < 0.0f)
		{
			currentCooldown = 0.0f;
		}
	}
}

void ABaseUltimateAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseUltimateAbility, cooldown);

	DOREPLIFETIME(ABaseUltimateAbility, currentCooldown);
}

ABaseUltimateAbility::ABaseUltimateAbility()
{
	NetUpdateFrequency = 60;
}

void ABaseUltimateAbility::applyAbility(ABaseCharacter* target)
{
	PURE_VIRTUAL(ABaseUltimateAbility::applyAbility)
}

void ABaseUltimateAbility::useAbility()
{
	if (!currentCooldown)
	{
		return;
	}

	currentCooldown = cooldown;
}
