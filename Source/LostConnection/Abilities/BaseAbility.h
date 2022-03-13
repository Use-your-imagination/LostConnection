// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "Animation/AnimMontage.h"
#include "Utility/Enums.h"

#include "Network/NetworkObject.h"

#include "BaseAbility.generated.h"

UCLASS(DefaultToInstanced)
class LOSTCONNECTION_API UBaseAbility : public UNetworkObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = AbilityInformation, EditDefaultsOnly, BlueprintReadOnly)
	FText name;

	UPROPERTY(Category = AbilityInformation, EditDefaultsOnly, BlueprintReadOnly)
	FText description;

	UPROPERTY(Category = AbilityInformation, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float cost;

	UPROPERTY(Category = UI, EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* icon;

	UPROPERTY(Category = AbilityState, EditDefaultsOnly, BlueprintReadOnly)
	bool isCancelable;

	UPROPERTY(Category = AbilityState, Replicated, BlueprintReadOnly)
	bool isDisabled;

	UPROPERTY(Category = AbilityState, EditDefaultsOnly, BlueprintReadOnly)
	bool isGrounded;

	UPROPERTY(Category = AbilityAnimation, EditDefaultsOnly, BlueprintReadOnly)
	float cancelBlendOutTime;

	UPROPERTY(Category = AbilityAnimation, EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* animation;

	EAbilitySlot id;

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

	virtual EAbilitySlot getId() const final;

	virtual class ICaster* getCaster() const final;

	virtual ~UBaseAbility() = default;
};
