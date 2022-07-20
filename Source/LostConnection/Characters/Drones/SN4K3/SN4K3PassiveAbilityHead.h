// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerInput.h"
#include "Net/UnrealNetwork.h"
#include "NiagaraSystem.h"

#include "Interfaces/Holders/AilmentInflictorHolder.h"

#include "SN4K3PassiveAbilityHead.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API ASN4K3PassiveAbilityHead :
	public ACharacter,
	public IAilmentInflictorHolder
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UNiagaraSystem> explosionParticles;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float explosionRadius;

	UPROPERTY(Category = SN4K3, Instanced, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UAilmentInflictorUtility> ailmentInflictorUtility;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

private:
	UFUNCTION(BlueprintCallable)
	void explode();

	void destroyHead();

public:
	ASN4K3PassiveAbilityHead();

	UFUNCTION(Category = RBM, BlueprintNativeEvent, BlueprintCallable)
	void speedup();

	UFUNCTION(Category = Checks, BlueprintNativeEvent, BlueprintCallable)
	bool checkExplode();

	UFUNCTION(Category = Checks, BlueprintNativeEvent, BlueprintCallable)
	bool checkSpeedup();

	UAilmentInflictorUtility* getAilmentInflictorUtility() const override;

	~ASN4K3PassiveAbilityHead() = default;
};
