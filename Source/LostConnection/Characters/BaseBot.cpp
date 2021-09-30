#include "BaseBot.h"

void ABaseBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(this) && isReadyForDestroy)
	{
		if (HasAuthority())
		{
			Destroy();
		}
	}
}

void ABaseBot::deathLogic()
{
	isReadyForDestroy = true;
}

ABaseBot::ABaseBot()
{
	isAlly = false;
	isReadyForDestroy = false;

	spareAmmo.Init(9999, 4);
}
