// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseBot.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

#include "Interfaces/Gameplay/AnimatedActions/Abilities/PassiveAbilityCast.h"
#include "Interfaces/Gameplay/AnimatedActions/Abilities/FirstAbilityCast.h"
#include "Interfaces/Gameplay/AnimatedActions/Abilities/SecondAbilityCast.h"
#include "Interfaces/Gameplay/AnimatedActions/Abilities/ThirdAbilityCast.h"
#include "Interfaces/Gameplay/AnimatedActions/Abilities/UltimateAbilityCast.h"

#include "BaseBotCaster.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseBotCaster : 
	public ABaseBot,
	public ICaster,
	public IPassiveAbilityCast,
	public IFirstAbilityCast,
	public ISecondAbilityCast,
	public IThirdAbilityCast,
	public IUltimateAbilityCast
{
	GENERATED_BODY()
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UFUNCTION()
	void onAbilityUsed();

protected:
	virtual bool checkPassiveAbilityCast() const override;

	virtual bool checkFirstAbilityCast() const override;

	virtual bool checkSecondAbilityCast() const override;

	virtual bool checkThirdAbilityCast() const override;

	virtual bool checkUltimateAbilityCast() const override;

	virtual float& getCurrentEnergy() final override;

protected:
	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float energy;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float currentEnergy;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float energyRestorationPerSecond;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float cooldownReduction;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float duration;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float power;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float energyEfficiency;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float AOE;

	UPROPERTY(Category = CasterStats, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float castPoint;

protected:
	UPROPERTY(Category = Abilities, ReplicatedUsing = onAbilityUsed, BlueprintReadOnly)
	EAbilitySlot abilityId;

	UPROPERTY(Category = Abilities, BlueprintReadOnly)
	UBaseAbility* currentAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UBasePassiveAbility* passiveAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UBaseAbility* firstAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UBaseAbility* secondAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UBaseAbility* thirdAbility;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	UBaseUltimateAbility* ultimateAbility;

	UPROPERTY(Category = Animations, EditDefaultsOnly, BlueprintReadOnly)
	TArray<UAnimMontage*> abilitiesAnimations;

protected:
	virtual void BeginPlay() override;

public:
	ABaseBotCaster();

	virtual void setEnergy_Implementation(float newEnergy) final override;

	virtual void setCurrentEnergy_Implementation(float newCurrentEnergy) final override;

	virtual void setEnergyRestorationPerSecond_Implementation(float newEnergyRestorationPerSecond) final override;

	virtual void setCooldownReduction_Implementation(float newCooldownReduction) final override;

	virtual void setDuration_Implementation(float newDuration) final;

	virtual void setPower_Implementation(float newPower) final;

	virtual void setEnergyEfficiency_Implementation(float newEnergyEfficiency) final;

	virtual void setAOE_Implementation(float newAOE) final;

	virtual void setCastPoint_Implementation(float newCastPoint) final;

	UFUNCTION(BlueprintCallable)
	virtual void setCurrentAbility(UBaseAbility* ability) final override;

	virtual float getEnergy() const final override;

	virtual float getCurrentEnergy() const final override;

	virtual float getEnergyRestorationPerSecond() const final override;

	virtual float getCooldownReduction() const final override;

	virtual float getDuration() const final;

	virtual float getPower() const final;

	virtual float getEnergyEfficiency() const final;

	virtual float getAOE() const final;

	virtual float getCastPoint() const final;

	virtual UBaseAbility* getCurrentAbility() const final override;

	virtual UBasePassiveAbility* getPassiveAbility() const final override;

	virtual UBaseAbility* getFirstAbility() const final override;

	virtual UBaseAbility* getSecondAbility() const final override;

	virtual UBaseAbility* getThirdAbility() const final override;

	virtual UBaseUltimateAbility* getUltimateAbility() const final override;

	virtual const TArray<UAnimMontage*>& getAbilitiesAnimations() const final override;

	virtual void castPassiveAbilityVisual() override;

	UFUNCTION(BlueprintCallable)
	virtual void castPassiveAbilityLogic() override;

	virtual void castFirstAbilityVisual() override;

	UFUNCTION(BlueprintCallable)
	virtual void castFirstAbilityLogic() override;

	virtual void castSecondAbilityVisual() override;

	UFUNCTION(BlueprintCallable)
	virtual void castSecondAbilityLogic() override;

	virtual void castThirdAbilityVisual() override;

	UFUNCTION(BlueprintCallable)
	virtual void castThirdAbilityLogic() override;

	virtual void castUltimateAbilityVisual() override;

	UFUNCTION(BlueprintCallable)
	virtual void castUltimateAbilityLogic() override;

	virtual ~ABaseBotCaster() = default;
};
