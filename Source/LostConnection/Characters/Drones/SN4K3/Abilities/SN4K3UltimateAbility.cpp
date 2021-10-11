#include "SN4K3UltimateAbility.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "Engine/LostConnectionGameState.h"
#include "WorldPlaceables/SN4K3/SN4K3UltimateAbilityPlaceholder.h"
#include "SN4K3PassiveAbility.h"

void USN4K3UltimateAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USN4K3UltimateAbility, isUltimateAbilityUsed);

	DOREPLIFETIME(USN4K3UltimateAbility, abilityDuration);

	DOREPLIFETIME(USN4K3UltimateAbility, currentAbilityDuration);
}

USN4K3UltimateAbility::USN4K3UltimateAbility() :
	abilityDuration(15.0f),
	currentAbilityDuration(0.0f)
{
	cooldown = 60.0f;
}

void USN4K3UltimateAbility::applyAbility(ABaseCharacter* target)
{
	ASN4K3* drone = Cast<ASN4K3>(target);
	ASN4K3UltimateAbilityPlaceholder* placeholder = drone->getUltimatePlaceholder();
	FVector returnPosition = placeholder->GetActorLocation();

	currentAbilityDuration = 0.0f;

	drone->setUltimatePlaceholder(nullptr);

	placeholder->Destroy();

	drone->SetActorLocation(returnPosition);

	ICaster::Execute_applyUltimateAbilityEvent(Cast<UObject>(caster), target);
}

void USN4K3UltimateAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(caster);
	FVector tem = drone->GetActorForwardVector() * 300;

	if (isUltimateAbilityUsed)
	{
		isUltimateAbilityUsed = false;

		this->applyAbility(drone);

		return;
	}
	else if (currentCooldown)
	{
		return;
	}

	tem.Z = -97.0f;

	isUltimateAbilityUsed = true;

	currentCooldown = cooldown;

	ASN4K3UltimateAbilityPlaceholder* placeholder = drone->GetWorld()->GetGameState<ALostConnectionGameState>()->spawn<ASN4K3UltimateAbilityPlaceholder>({ drone->GetActorRotation(), tem + drone->GetActorLocation() });

	placeholder->setAbility(this);

	placeholder->FinishSpawning({}, true);

	drone->setUltimatePlaceholder(placeholder);

	Cast<USN4K3PassiveAbility>(drone->getPassiveAbility())->resetLastTimeAbilityUsed();
}

void USN4K3UltimateAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ASN4K3* drone = Cast<ASN4K3>(caster);

	if (isUltimateAbilityUsed)
	{
		currentAbilityDuration += DeltaTime;

		if (currentAbilityDuration >= abilityDuration)
		{
			isUltimateAbilityUsed = false;

			this->applyAbility(drone);
		}
	}
}
