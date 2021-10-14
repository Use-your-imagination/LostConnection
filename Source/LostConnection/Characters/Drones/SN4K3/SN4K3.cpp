#include "SN4K3.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Abilities/SN4K3PassiveAbility.h"
#include "Abilities/SN4K3FirstAbility.h"
#include "Abilities/SN4K3SecondAbility.h"
#include "Abilities/SN4K3ThirdAbility.h"
#include "Abilities/SN4K3UltimateAbility.h"
#include "WorldPlaceables/SN4K3/SN4K3UltimateAbilityPlaceholder.h"

void ASN4K3::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		passiveAbility = NewObject<USN4K3PassiveAbility>();
		firstAbility = NewObject<USN4K3FirstAbility>();
		secondAbility = NewObject<USN4K3SecondAbility>();
		thirdAbility = NewObject<USN4K3ThirdAbility>();
		ultimateAbility = NewObject<USN4K3UltimateAbility>();

		passiveAbility->setCaster(this);
		firstAbility->setCaster(this);
		secondAbility->setCaster(this);
		thirdAbility->setCaster(this);
		ultimateAbility->setCaster(this);
	}
}

void ASN4K3::onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* target = Cast<ABaseCharacter>(OtherActor);

	if (!target || isAlly == target->getIsAlly())
	{
		return;
	}

	firstAbility->applyAbility(target);
}

ASN4K3::ASN4K3()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASN4K3::onBeginOverlap);

	spareAmmo[static_cast<size_t>(ammoTypes::large)] = 120;
	spareAmmo[static_cast<size_t>(ammoTypes::energy)] = 180;
}

void ASN4K3::setUltimatePlaceholder(ASN4K3UltimateAbilityPlaceholder* ultimatePlaceholder)
{
	this->ultimatePlaceholder = ultimatePlaceholder;
}

ASN4K3UltimateAbilityPlaceholder* ASN4K3::getUltimatePlaceholder()
{
	return ultimatePlaceholder;
}
