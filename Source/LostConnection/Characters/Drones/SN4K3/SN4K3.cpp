#include "SN4K3.h"

#include "Abilities/SN4K3PassiveAbility.h"
#include "Abilities/SN4K3FirstAbility.h"
#include "Abilities/SN4K3SecondAbility.h"
#include "Abilities/SN4K3ThirdAbility.h"
#include "Abilities/SN4K3UltimateAbility.h"

void ASN4K3::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		passiveAbility = NewObject<ASN4K3PassiveAbility>();
		firstAbility = NewObject<ASN4K3FirstAbility>();
		secondAbility = NewObject<ASN4K3SecondAbility>();
		thirdAbility = NewObject<ASN4K3ThirdAbility>();
		ultimateAbility = NewObject<ASN4K3UltimateAbility>();

		passiveAbility->setOwner(this);
		firstAbility->setOwner(this);
		secondAbility->setOwner(this);
		thirdAbility->setOwner(this);
		ultimateAbility->setOwner(this);
	}
}

void ASN4K3::onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

ASN4K3::ASN4K3()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASN4K3::onBeginOverlap);
}
