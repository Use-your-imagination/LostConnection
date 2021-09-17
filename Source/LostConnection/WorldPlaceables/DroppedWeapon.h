// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DroppedObject.h"
#include "Weapons/BaseWeapon.h"

#include "DroppedWeapon.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ADroppedWeapon : public ADroppedObject
{
	GENERATED_BODY()

private:
	virtual void Tick(float DeltaSeconds) final override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UFUNCTION()
	virtual void onWeaponChange() final;

private:
	UPROPERTY(ReplicatedUsing = onWeaponChange)
	UBaseWeapon* weapon;

protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* magazine;

public:
	ADroppedWeapon();

	UFUNCTION(Server, Reliable)
	void setWeapon(UBaseWeapon* newWeapon);

	UBaseWeapon* getWeapon();

	virtual void setMesh(USkeletalMesh* mesh) final override;

	virtual void action(AActor* player) final override;

	~ADroppedWeapon() = default;
};
