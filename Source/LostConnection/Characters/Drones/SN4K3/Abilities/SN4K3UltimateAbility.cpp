#include "SN4K3UltimateAbility.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Engine/LostConnectionGameState.h"
#include "WorldPlaceables/SN4K3/SN4K3UltimateAbilityPlaceholder.h"

ASN4K3UltimateAbility::ASN4K3UltimateAbility() :
	abilityDuration(15.0f),
	currentAbilityDuration(0.0f)
{
	cooldown = 60.0f;
}

void ASN4K3UltimateAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ASN4K3* drone = Cast<ASN4K3>(owner);

	if (currentCooldown > 0.0f)
	{
		currentCooldown -= DeltaTime;

		if (currentCooldown < 0.0f)
		{
			currentCooldown = 0.0f;
		}
	}

	if (drone->getIsUltimateAbilityUsed())
	{
		currentAbilityDuration += DeltaTime;

		if (currentAbilityDuration >= abilityDuration)
		{
			drone->getIsUltimateAbilityUsed() = false;

			this->applyAbility(drone);
		}
	}
}

void ASN4K3UltimateAbility::applyAbility(ABaseCharacter* target)
{
	ASN4K3* drone = Cast<ASN4K3>(target);
	ASN4K3UltimateAbilityPlaceholder* placeholder = drone->getUltimatePlaceholder();
	FVector returnPosition = placeholder->GetActorLocation();

	currentAbilityDuration = 0.0f;

	drone->setUltimatePlaceholder(nullptr);

	placeholder->Destroy();

	drone->SetActorLocation(returnPosition);

	ICaster::Execute_applyUltimateAbilityEvent(Cast<UObject>(owner), target);
}

void ASN4K3UltimateAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(owner);
	FVector tem = drone->GetActorForwardVector() * 300;
	bool& isUltimateAbilityPressed = drone->getIsUltimateAbilityUsed();

	if (isUltimateAbilityPressed)
	{
		isUltimateAbilityPressed = false;

		this->applyAbility(drone);

		return;
	}
	else if (currentCooldown)
	{
		return;
	}

	tem.Z = -97.0f;

	isUltimateAbilityPressed = true;

	currentCooldown = cooldown;

	ASN4K3UltimateAbilityPlaceholder* placeholder = drone->GetWorld()->GetGameState<ALostConnectionGameState>()->spawn<ASN4K3UltimateAbilityPlaceholder>({ drone->GetActorRotation(), tem + drone->GetActorLocation() });

	placeholder->setAbility(this);

	placeholder->FinishSpawning({}, true);

	drone->setUltimatePlaceholder(placeholder);
}
