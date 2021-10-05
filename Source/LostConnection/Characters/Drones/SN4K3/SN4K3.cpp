#include "SN4K3.h"

#include "Abilities/SN4K3PassiveAbility.h"
#include "Abilities/SN4K3FirstAbility.h"
#include "Abilities/SN4K3SecondAbility.h"
#include "Abilities/SN4K3ThirdAbility.h"
#include "Abilities/SN4K3UltimateAbility.h"

ASN4K3::ASN4K3()
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
