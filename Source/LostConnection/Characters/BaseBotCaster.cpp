// Copyright (c) 2021 Use-your-imagination

#include "BaseBotCaster.h"

#include "GameFramework/CharacterMovementComponent.h"

void ABaseBotCaster::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseBotCaster, energy);

	DOREPLIFETIME(ABaseBotCaster, currentEnergy);

	DOREPLIFETIME(ABaseBotCaster, energyRestorationPerSecond);

	DOREPLIFETIME(ABaseBotCaster, cooldownReduction);

	DOREPLIFETIME(ABaseBotCaster, duration);

	DOREPLIFETIME(ABaseBotCaster, power);

	DOREPLIFETIME(ABaseBotCaster, energyEfficiency);

	DOREPLIFETIME(ABaseBotCaster, AOE);

	DOREPLIFETIME(ABaseBotCaster, castPoint);

	DOREPLIFETIME(ABaseBotCaster, abilityId);

	DOREPLIFETIME(ABaseBotCaster, passiveAbility);

	DOREPLIFETIME(ABaseBotCaster, firstAbility);

	DOREPLIFETIME(ABaseBotCaster, secondAbility);

	DOREPLIFETIME(ABaseBotCaster, thirdAbility);

	DOREPLIFETIME(ABaseBotCaster, ultimateAbility);
}

bool ABaseBotCaster::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (passiveAbility)
	{
		wroteSomething |= passiveAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);

		wroteSomething |= Channel->ReplicateSubobject(passiveAbility, *Bunch, *RepFlags);
	}

	if (firstAbility)
	{
		wroteSomething |= Channel->ReplicateSubobject(firstAbility, *Bunch, *RepFlags);

		wroteSomething |= firstAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (secondAbility)
	{
		wroteSomething |= Channel->ReplicateSubobject(secondAbility, *Bunch, *RepFlags);

		wroteSomething |= secondAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (thirdAbility)
	{
		wroteSomething |= Channel->ReplicateSubobject(thirdAbility, *Bunch, *RepFlags);

		wroteSomething |= thirdAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (ultimateAbility)
	{
		wroteSomething |= Channel->ReplicateSubobject(ultimateAbility, *Bunch, *RepFlags);

		wroteSomething |= ultimateAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return wroteSomething;
}

void ABaseBotCaster::onAbilityUsed()
{
	switch (abilityId)
	{
	case abilitySlot::empty:
		currentAbility = nullptr;

		break;

	case abilitySlot::passiveAbility:
		currentAbility = passiveAbility;

		break;

	case abilitySlot::firstAbility:
		currentAbility = firstAbility;

		break;

	case abilitySlot::secondAbility:
		currentAbility = secondAbility;

		break;

	case abilitySlot::thirdAbility:
		currentAbility = thirdAbility;

		break;

	case abilitySlot::ultimateAbility:
		currentAbility = ultimateAbility;

		break;
	}
}

bool ABaseBotCaster::checkPassiveAbilityCast() const
{
	return true;
}

bool ABaseBotCaster::checkFirstAbilityCast() const
{
	if (firstAbility->getIsDisabled() ||
		currentAbility ||
		currentEnergy < firstAbility->getCost() ||
		(firstAbility->getIsGrounded() && GetCharacterMovement()->IsFalling()))
	{
		return false;
	}

	return true;
}

bool ABaseBotCaster::checkSecondAbilityCast() const
{
	if (secondAbility->getIsDisabled() ||
		currentAbility ||
		currentEnergy < secondAbility->getCost() ||
		(secondAbility->getIsGrounded() && GetCharacterMovement()->IsFalling()))
	{
		return false;
	}

	return true;
}

bool ABaseBotCaster::checkThirdAbilityCast() const
{
	if (thirdAbility->getIsDisabled() ||
		currentAbility ||
		currentEnergy < thirdAbility->getCost() ||
		(thirdAbility->getIsGrounded() && GetCharacterMovement()->IsFalling()))
	{
		return false;
	}

	return true;
}

bool ABaseBotCaster::checkUltimateAbilityCast() const
{
	if (ultimateAbility->getIsDisabled() ||
		currentAbility ||
		currentEnergy < ultimateAbility->getCost() ||
		!ultimateAbility->getCurrentCooldown() ||
		(ultimateAbility->getIsGrounded() && GetCharacterMovement()->IsFalling()))
	{
		return false;
	}

	return true;
}

void ABaseBotCaster::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		passiveAbility->initAbility();

		firstAbility->initAbility();

		secondAbility->initAbility();

		thirdAbility->initAbility();

		ultimateAbility->initAbility();
	}
}

ABaseBotCaster::ABaseBotCaster()
{

}

void ABaseBotCaster::setEnergy_Implementation(float newEnergy)
{
	energy = newEnergy;
}

void ABaseBotCaster::setCurrentEnergy_Implementation(float newCurrentEnergy)
{
	if (newCurrentEnergy > energy)
	{
		currentEnergy = energy;
	}
	else
	{
		currentEnergy = newCurrentEnergy;
	}
}

void ABaseBotCaster::setEnergyRestorationPerSecond_Implementation(float newEnergyRestorationPerSecond)
{
	energyRestorationPerSecond = newEnergyRestorationPerSecond;
}

void ABaseBotCaster::setCooldownReduction_Implementation(float newCooldownReduction)
{
	cooldownReduction = newCooldownReduction;
}

void ABaseBotCaster::setDuration_Implementation(float newDuration)
{
	duration = newDuration;
}

void ABaseBotCaster::setPower_Implementation(float newPower)
{
	power = newPower;
}

void ABaseBotCaster::setEnergyEfficiency_Implementation(float newEnergyEfficiency)
{
	energyEfficiency = newEnergyEfficiency;
}

void ABaseBotCaster::setAOE_Implementation(float newAOE)
{
	AOE = newAOE;
}

void ABaseBotCaster::setCastPoint_Implementation(float newCastPoint)
{
	castPoint = newCastPoint;
}

void ABaseBotCaster::setCurrentAbility_Implementation(UBaseAbility* ability)
{
	if (ability)
	{
		abilityId = ability->getId();
	}
	else
	{
		abilityId = abilitySlot::empty;
	}

	this->onAbilityUsed();
}

float ABaseBotCaster::getEnergy() const
{
	return energy;
}

float ABaseBotCaster::getCurrentEnergy() const
{
	return currentEnergy;
}

float ABaseBotCaster::getEnergyRestorationPerSecond() const
{
	return energyRestorationPerSecond;
}

float ABaseBotCaster::getCooldownReduction() const
{
	return cooldownReduction;
}

float ABaseBotCaster::getDuration() const
{
	return duration;
}

float ABaseBotCaster::getPower() const
{
	return power;
}

float ABaseBotCaster::getEnergyEfficiency() const
{
	return energyEfficiency;
}

float ABaseBotCaster::getAOE() const
{
	return AOE;
}

float ABaseBotCaster::getCastPoint() const
{
	return castPoint;
}

UBaseAbility* ABaseBotCaster::getCurrentAbility() const
{
	return currentAbility;
}

UBasePassiveAbility* ABaseBotCaster::getPassiveAbility() const
{
	return passiveAbility;
}

UBaseAbility* ABaseBotCaster::getFirstAbility() const
{
	return firstAbility;
}

UBaseAbility* ABaseBotCaster::getSecondAbility() const
{
	return secondAbility;
}

UBaseAbility* ABaseBotCaster::getThirdAbility() const
{
	return thirdAbility;
}

UBaseUltimateAbility* ABaseBotCaster::getUltimateAbility() const
{
	return ultimateAbility;
}

const TArray<UAnimMontage*>& ABaseBotCaster::getAbilitiesAnimations() const
{
	return abilitiesAnimations;
}

#pragma region PassiveAbility
void ABaseBotCaster::castPassiveAbilityVisual()
{

}

void ABaseBotCaster::castPassiveAbilityLogic_Implementation()
{
	currentEnergy -= passiveAbility->getCost();

	passiveAbility->useAbility();

	IPassiveAbilityCast::Execute_castPassiveAbilityEventLogic(this);
}
#pragma endregion

#pragma region FirstAbility
void ABaseBotCaster::castFirstAbilityVisual()
{

}

void ABaseBotCaster::castFirstAbilityLogic_Implementation()
{
	currentEnergy -= firstAbility->getCost();

	firstAbility->useAbility();

	IFirstAbilityCast::Execute_castFirstAbilityEventLogic(this);
}
#pragma endregion

#pragma region SecondAbility
void ABaseBotCaster::castSecondAbilityVisual()
{

}

void ABaseBotCaster::castSecondAbilityLogic_Implementation()
{
	currentEnergy -= secondAbility->getCost();

	secondAbility->useAbility();

	ISecondAbilityCast::Execute_castSecondAbilityEventLogic(this);
}
#pragma endregion

#pragma region ThirdAbility
void ABaseBotCaster::castThirdAbilityVisual()
{

}

void ABaseBotCaster::castThirdAbilityLogic_Implementation()
{
	currentEnergy -= thirdAbility->getCost();

	thirdAbility->useAbility();

	IThirdAbilityCast::Execute_castThirdAbilityEventLogic(this);
}
#pragma endregion

#pragma region UltimateAbility
void ABaseBotCaster::castUltimateAbilityVisual()
{

}

void ABaseBotCaster::castUltimateAbilityLogic_Implementation()
{
	currentEnergy -= ultimateAbility->getCost();

	ultimateAbility->useAbility();

	IUltimateAbilityCast::Execute_castUltimateAbilityEventLogic(this);
}
#pragma endregion
