// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"

#include "BaseAbility.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API UBaseAbility : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Abilities, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float cost;

	UPROPERTY(Category = Abilities, VisibleAnywhere, Replicated, BlueprintReadOnly)
	bool isDisabled;

	UPROPERTY(Category = Abilities, VisibleAnywhere, BlueprintReadOnly)
	FString localizedName;

	UPROPERTY(Category = Abilities, VisibleAnywhere, BlueprintReadOnly)
	FString description;

	class ICaster* caster;
	FString name;

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

	virtual const FString& getLocalizedName() const final;

	virtual class ICaster* getCaster() final;

	virtual ~UBaseAbility() = default;
};
