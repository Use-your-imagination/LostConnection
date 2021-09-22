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
	AActor* owner;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void useAbility(AActor* target);

public:
	ABaseAbility();

	UFUNCTION(Server, Reliable)
	virtual void setCost(float newCost) final;

	virtual void setOwner(AActor* owner) final;

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
