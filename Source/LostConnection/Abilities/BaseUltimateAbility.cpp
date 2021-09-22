#include "BaseUltimateAbility.h"

#include "Characters/BaseDrone.h"

void ABaseUltimateAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority() && currentCooldown > 0.0f)
	{
		currentCooldown -= DeltaTime;
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

void ABaseUltimateAbility::applyAbility(ABaseDrone* target)
{
	PURE_VIRTUAL(ABaseUltimateAbility::applyAbility)
}

void ABaseUltimateAbility::useAbility()
{
	currentCooldown = cooldown;
}
