#include "SN4K3ThirdAbility.h"

#include "Characters/Drones/SN4K3/SN4K3.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"
#include "WorldPlaceables/SN4K3/SN4K3ThirdAbilityFlag.h"

ASN4K3ThirdAbility::ASN4K3ThirdAbility()
{

}

void ASN4K3ThirdAbility::applyAbility(ABaseCharacter* target)
{
	ICaster::Execute_applyThirdAbilityEvent(Cast<UObject>(owner), target);
}

void ASN4K3ThirdAbility::useAbility()
{
	ASN4K3* drone = Cast<ASN4K3>(owner);

	drone->GetWorld()->SpawnActor<ASN4K3ThirdAbilityFlag>(ASN4K3ThirdAbilityFlag::StaticClass(), FVector(drone->GetActorForwardVector() * 300) + drone->GetActorLocation(), FRotator());
}
