#include "SN4K3.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Abilities/SN4K3PassiveAbility.h"
#include "Abilities/SN4K3FirstAbility.h"
#include "Abilities/SN4K3SecondAbility.h"
#include "Abilities/SN4K3ThirdAbility.h"
#include "Abilities/SN4K3UltimateAbility.h"
#include "WorldPlaceables/SN4K3/SN4K3UltimateAbilityPlaceholder.h"

void ASN4K3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		passiveAbility->useAbility();

		Cast<ASN4K3UltimateAbility>(ultimateAbility)->Tick(DeltaTime);
	}
}

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

void ASN4K3::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASN4K3, naniteMeter);

	DOREPLIFETIME(ASN4K3, isUltimateAbilityPressed);
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

ASN4K3::ASN4K3() :
	naniteMeter(0),
	isUltimateAbilityPressed(false)
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASN4K3::onBeginOverlap);

	spareAmmo[static_cast<size_t>(ammoTypes::large)] = 120;
	spareAmmo[static_cast<size_t>(ammoTypes::energy)] = 180;
}

void ASN4K3::setUltimatePlaceholder(ASN4K3UltimateAbilityPlaceholder* ultimatePlaceholder)
{
	this->ultimatePlaceholder = ultimatePlaceholder;
}

bool& ASN4K3::getIsUltimateAbilityUsed()
{
	return isUltimateAbilityPressed;
}

ASN4K3UltimateAbilityPlaceholder* ASN4K3::getUltimatePlaceholder()
{
	return ultimatePlaceholder;
}

void ASN4K3::castFirstAbilityVisual()
{
	if (HasAuthority())
	{
		this->castFirstAbilityLogic();
	}
}

void ASN4K3::castSecondAbilityVisual()
{
	if (HasAuthority())
	{
		this->castSecondAbilityLogic();
	}
}

void ASN4K3::castThirdAbilityVisual()
{
	if (HasAuthority())
	{
		this->castThirdAbilityLogic();
	}
}

void ASN4K3::castUltimateAbilityVisual()
{
	if (HasAuthority())
	{
		this->castUltimateAbilityLogic();
	}
}
