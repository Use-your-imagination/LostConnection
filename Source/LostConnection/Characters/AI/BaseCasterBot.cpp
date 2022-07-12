// Copyright (c) 2021 Use Your Imagination

#include "BaseCasterBot.h"

#include "GameFramework/CharacterMovementComponent.h"

void ABaseCasterBot::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCasterBot, energy);

	DOREPLIFETIME(ABaseCasterBot, currentEnergy);

	DOREPLIFETIME(ABaseCasterBot, energyRestorationPerSecond);

	DOREPLIFETIME(ABaseCasterBot, cooldownReduction);

	DOREPLIFETIME(ABaseCasterBot, duration);

	DOREPLIFETIME(ABaseCasterBot, power);

	DOREPLIFETIME(ABaseCasterBot, energyEfficiency);

	DOREPLIFETIME(ABaseCasterBot, AOE);

	DOREPLIFETIME(ABaseCasterBot, castPoint);

	DOREPLIFETIME(ABaseCasterBot, abilityId);

	DOREPLIFETIME(ABaseCasterBot, passiveAbility);

	DOREPLIFETIME(ABaseCasterBot, firstAbility);

	DOREPLIFETIME(ABaseCasterBot, secondAbility);

	DOREPLIFETIME(ABaseCasterBot, thirdAbility);

	DOREPLIFETIME(ABaseCasterBot, ultimateAbility);
}

bool ABaseCasterBot::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (IsValid(passiveAbility))
	{
		wroteSomething |= passiveAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);

		wroteSomething |= Channel->ReplicateSubobject(passiveAbility, *Bunch, *RepFlags);
	}

	if (IsValid(firstAbility))
	{
		wroteSomething |= Channel->ReplicateSubobject(firstAbility, *Bunch, *RepFlags);

		wroteSomething |= firstAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(secondAbility))
	{
		wroteSomething |= Channel->ReplicateSubobject(secondAbility, *Bunch, *RepFlags);

		wroteSomething |= secondAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(thirdAbility))
	{
		wroteSomething |= Channel->ReplicateSubobject(thirdAbility, *Bunch, *RepFlags);

		wroteSomething |= thirdAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	if (IsValid(ultimateAbility))
	{
		wroteSomething |= Channel->ReplicateSubobject(ultimateAbility, *Bunch, *RepFlags);

		wroteSomething |= ultimateAbility->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return wroteSomething;
}

void ABaseCasterBot::onAbilityUsed()
{
	switch (abilityId)
	{
	case EAbilitySlot::empty:
		currentAbility = nullptr;

		break;

	case EAbilitySlot::passiveAbility:
		currentAbility = passiveAbility;

		break;

	case EAbilitySlot::firstAbility:
		currentAbility = firstAbility;

		break;

	case EAbilitySlot::secondAbility:
		currentAbility = secondAbility;

		break;

	case EAbilitySlot::thirdAbility:
		currentAbility = thirdAbility;

		break;

	case EAbilitySlot::ultimateAbility:
		currentAbility = ultimateAbility;

		break;
	}
}

bool ABaseCasterBot::checkPassiveAbilityCast() const
{
	return true;
}

bool ABaseCasterBot::checkFirstAbilityCast() const
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

bool ABaseCasterBot::checkSecondAbilityCast() const
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

bool ABaseCasterBot::checkThirdAbilityCast() const
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

bool ABaseCasterBot::checkUltimateAbilityCast() const
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

float& ABaseCasterBot::getCurrentEnergy()
{
	return currentEnergy;
}

void ABaseCasterBot::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		TObjectPtr<AController> controller = GetController();

		passiveAbility->initAbility(controller);

		firstAbility->initAbility(controller);

		secondAbility->initAbility(controller);

		thirdAbility->initAbility(controller);

		ultimateAbility->initAbility(controller);
	}
}

TArray<TScriptInterface<IOnCastEvent>>& ABaseCasterBot::getCastEvents()
{
	return castEvents;
}

ABaseCasterBot::ABaseCasterBot()
{

}

void ABaseCasterBot::setEnergy_Implementation(float newEnergy)
{
	energy = newEnergy;
}

void ABaseCasterBot::setCurrentEnergy_Implementation(float newCurrentEnergy)
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

void ABaseCasterBot::setEnergyRestorationPerSecond_Implementation(float newEnergyRestorationPerSecond)
{
	energyRestorationPerSecond = newEnergyRestorationPerSecond;
}

void ABaseCasterBot::setCooldownReduction_Implementation(float newCooldownReduction)
{
	cooldownReduction = newCooldownReduction;
}

void ABaseCasterBot::setDuration_Implementation(float newDuration)
{
	duration = newDuration;
}

void ABaseCasterBot::setPower_Implementation(float newPower)
{
	power = newPower;
}

void ABaseCasterBot::setEnergyEfficiency_Implementation(float newEnergyEfficiency)
{
	energyEfficiency = newEnergyEfficiency;
}

void ABaseCasterBot::setAOE_Implementation(float newAOE)
{
	AOE = newAOE;
}

void ABaseCasterBot::setCastPoint_Implementation(float newCastPoint)
{
	castPoint = newCastPoint;
}

void ABaseCasterBot::setCurrentAbility(UBaseAbility* ability)
{
	if (ability)
	{
		abilityId = ability->getId();
	}
	else
	{
		abilityId = EAbilitySlot::empty;
	}

	this->onAbilityUsed();
}

float ABaseCasterBot::getEnergy() const
{
	return energy;
}

float ABaseCasterBot::getCurrentEnergy() const
{
	return currentEnergy;
}

float ABaseCasterBot::getEnergyRestorationPerSecond() const
{
	return energyRestorationPerSecond;
}

float ABaseCasterBot::getCooldownReduction() const
{
	return cooldownReduction;
}

float ABaseCasterBot::getDuration() const
{
	return duration;
}

float ABaseCasterBot::getPower() const
{
	return power;
}

float ABaseCasterBot::getEnergyEfficiency() const
{
	return energyEfficiency;
}

float ABaseCasterBot::getAOE() const
{
	return AOE;
}

float ABaseCasterBot::getCastPoint() const
{
	return castPoint;
}

UBaseAbility* ABaseCasterBot::getCurrentAbility() const
{
	return currentAbility;
}

UBasePassiveAbility* ABaseCasterBot::getPassiveAbility() const
{
	return passiveAbility;
}

UBaseAbility* ABaseCasterBot::getFirstAbility() const
{
	return firstAbility;
}

UBaseAbility* ABaseCasterBot::getSecondAbility() const
{
	return secondAbility;
}

UBaseAbility* ABaseCasterBot::getThirdAbility() const
{
	return thirdAbility;
}

UBaseUltimateAbility* ABaseCasterBot::getUltimateAbility() const
{
	return ultimateAbility;
}

const TArray<UAnimMontage*>& ABaseCasterBot::getAbilitiesAnimations() const
{
	return abilitiesAnimations;
}

void ABaseCasterBot::castPassiveAbilityVisual()
{

}

void ABaseCasterBot::castPassiveAbilityLogic()
{
	this->castAbility(passiveAbility, [this]()
		{
			IPassiveAbilityCast::Execute_castPassiveAbilityEventLogic(this);
		});
}

void ABaseCasterBot::castFirstAbilityVisual()
{

}

void ABaseCasterBot::castFirstAbilityLogic()
{
	this->castAbility(firstAbility, [this]()
		{
			IFirstAbilityCast::Execute_castFirstAbilityEventLogic(this);
		});
}

void ABaseCasterBot::castSecondAbilityVisual()
{

}

void ABaseCasterBot::castSecondAbilityLogic()
{
	this->castAbility(secondAbility, [this]()
		{
			ISecondAbilityCast::Execute_castSecondAbilityEventLogic(this);
		});
}

void ABaseCasterBot::castThirdAbilityVisual()
{

}

void ABaseCasterBot::castThirdAbilityLogic()
{
	this->castAbility(thirdAbility, [this]()
		{
			IThirdAbilityCast::Execute_castThirdAbilityEventLogic(this);
		});
}

void ABaseCasterBot::castUltimateAbilityVisual()
{

}

void ABaseCasterBot::castUltimateAbilityLogic()
{
	this->castAbility(ultimateAbility, [this]()
		{
			IUltimateAbilityCast::Execute_castUltimateAbilityEventLogic(this);
		});
}
