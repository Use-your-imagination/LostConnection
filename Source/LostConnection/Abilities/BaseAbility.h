// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "Animation/AnimMontage.h"

#include "Network/NetworkObject.h"

#include "BaseAbility.generated.h"

UENUM(BlueprintType)
enum class abilitySlot : uint8
{
	empty = 0 UMETA(DisplayName = "No ability"),
	passiveAbility = 1 UMETA(DisplayName = "Passive ability"),
	firstAbility = 2 UMETA(DisplayName = "First ability"),
	secondAbility = 3 UMETA(DisplayName = "Second ability"),
	thirdAbility = 4 UMETA(DisplayName = "Third ability"),
	ultimateAbility = 5 UMETA(DisplayName = "Ultimate ability")
};

UCLASS(DefaultToInstanced)
class LOSTCONNECTION_API UBaseAbility : public UNetworkObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = "Ability Information", EditDefaultsOnly, BlueprintReadOnly)
	FText name;

	UPROPERTY(Category = "Ability Information", EditDefaultsOnly, BlueprintReadOnly)
	FText description;

	UPROPERTY(Category = "Ability Information", EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float cost;

	UPROPERTY(Category = UI, EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* icon;

	UPROPERTY(Category = "Ability State", EditDefaultsOnly, BlueprintReadOnly)
	bool isCancelable;

	UPROPERTY(Category = "Ability State", Replicated, BlueprintReadOnly)
	bool isDisabled;

	UPROPERTY(Category = "Ability State", EditDefaultsOnly, BlueprintReadOnly)
	bool isGrounded;

	UPROPERTY(Category = "Ability Animation", EditDefaultsOnly, BlueprintReadOnly)
	float cancelBlendOutTime;

	UPROPERTY(Category = "Ability Animation", EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* animation;

	abilitySlot id;

	class ICaster* caster;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBaseAbility();

	virtual void applyAbility(class ABaseCharacter* target);

	virtual void useAbility();

	virtual void Tick(float DeltaTime);

	virtual void initAbility();

	UFUNCTION(Server, Reliable)
	virtual void setCost(float newCost) final;

	virtual void setCaster(class ICaster* caster) final;

	UFUNCTION(Server, Reliable)
	virtual void disable() final;

	UFUNCTION(Server, Reliable)
	virtual void enable() final;

	virtual float getCost() const final;

	virtual bool getIsDisabled() const final;

	virtual const FText& getName() const final;

	virtual const FText& getDescription() const final;

	virtual bool getIsCancelable() const final;

	virtual bool getIsGrounded() const final;

	virtual float getCancelBlendOutTime() const final;

	virtual UAnimMontage* getAnimation() final;

	virtual abilitySlot getId() const final;

	virtual class ICaster* getCaster() const final;

	virtual ~UBaseAbility() = default;
};
