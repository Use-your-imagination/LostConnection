// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"

#include "BaseAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseAbility : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Replicated)
	float cost;

	UPROPERTY(Replicated)
	bool isDisabled;

	FString name;
	FString localizedName;
	FString description;
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

	UFUNCTION(BlueprintCallable)
	virtual float getCost() const final;

	UFUNCTION(BlueprintCallable)
	virtual bool getIsDisabled() const final;

	UFUNCTION(BlueprintCallable)
	virtual const FString& getLocalizedName() const final;

	UFUNCTION(BlueprintCallable)
	virtual AActor* getCasterCaster() final;

	virtual ~UBaseAbility() = default;
};
