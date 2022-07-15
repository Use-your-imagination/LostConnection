// Copyright (c) 2021 Use Your Imagination

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
	TObjectPtr<UTexture2D> icon;

	UPROPERTY(Category = AbilityState, EditDefaultsOnly, BlueprintReadOnly)
	bool isCancelable;

	UPROPERTY(Category = AbilityState, Replicated, BlueprintReadOnly)
	bool isDisabled;

	UPROPERTY(Category = AbilityState, EditDefaultsOnly, BlueprintReadOnly)
	bool isGrounded;

	UPROPERTY(Category = AbilityAnimation, EditDefaultsOnly, BlueprintReadOnly)
	float cancelBlendOutTime;

	UPROPERTY(Category = AbilityAnimation, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> animation;

	UPROPERTY()
	TScriptInterface<class ICaster> caster;

	UPROPERTY()
	TObjectPtr<AController> instigator;

	EAbilitySlot id;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBaseAbility();

	virtual void applyAbility(class ABaseCharacter* target);

	virtual void useAbility();

	virtual void Tick(float DeltaSeconds);

	virtual void initAbility(const TObjectPtr<AController>& instigator);

	UFUNCTION(Server, Reliable)
	void setCost(float newCost);

	void setCaster(TScriptInterface<class ICaster> caster);

	UFUNCTION(Server, Reliable)
	void disable();

	UFUNCTION(Server, Reliable)
	void enable();

	float getCost() const;

	bool getIsDisabled() const;

	const FText& getName() const;

	const FText& getDescription() const;

	bool getIsCancelable() const;

	bool getIsGrounded() const;

	float getCancelBlendOutTime() const;

	TObjectPtr<UAnimMontage> getAnimation();

	EAbilitySlot getId() const;

	const TScriptInterface<class ICaster>& getCaster() const;

	virtual ~UBaseAbility() = default;
};
