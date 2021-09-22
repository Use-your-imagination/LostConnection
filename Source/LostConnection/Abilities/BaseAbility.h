// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"

#include "BaseAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseAbility : public AActor
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
	class ABaseDrone* owner;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	ABaseAbility();

	virtual void applyAbility(class ABaseDrone* target);

	virtual void useAbility();

	UFUNCTION(Server, Reliable)
	virtual void setCost(float newCost) final;

	virtual void setOwner(class ABaseDrone* owner) final;

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

	virtual ~ABaseAbility() = default;
};
