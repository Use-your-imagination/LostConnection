#include "BaseUltimateAbility.h"

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

void ABaseUltimateAbility::useAbility(AActor* target)
{
	currentCooldown = cooldown;
}

ABaseUltimateAbility::ABaseUltimateAbility()
{
	NetUpdateFrequency = 60;
}
