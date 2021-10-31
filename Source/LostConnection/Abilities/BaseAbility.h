#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "Animation/AnimMontage.h"
#include "Net/UnrealNetwork.h"

#include "BaseAbility.generated.h"

UCLASS(BlueprintType, DefaultToInstanced)
class LOSTCONNECTION_API UBaseAbility : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Abilities, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float cost;

	UPROPERTY(Category = Abilities, VisibleAnywhere, Replicated, BlueprintReadOnly)
	bool isDisabled;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, BlueprintReadOnly)
	FText name;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, BlueprintReadOnly)
	FText description;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, BlueprintReadOnly)
	bool isCancelable;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, BlueprintReadOnly)
	bool isGrounded;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, BlueprintReadOnly)
	float cancelBlendOutTime;

	UPROPERTY(Category = Abilities, EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* animation;

	class ICaster* caster;

protected:
	virtual bool IsSupportedForNetworking() const final override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBaseAbility();

	virtual void applyAbility(class ABaseCharacter* target);

	virtual void useAbility();

	virtual void Tick(float DeltaTime);

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

	virtual class ICaster* getCaster() final;

	virtual ~UBaseAbility() = default;
};
