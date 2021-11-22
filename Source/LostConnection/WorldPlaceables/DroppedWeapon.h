// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "DroppedObject.h"
#include "Weapons/BaseWeapon.h"
#include "Interfaces/Gameplay/Descriptions/Actionable.h"

#include "DroppedWeapon.generated.h"

UCLASS()
class LOSTCONNECTION_API ADroppedWeapon : 
	public ADroppedObject,
	public IActionable
{
	GENERATED_BODY()

private:
	virtual void Tick(float DeltaTime) final override;

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

	virtual void action(class ABaseDrone* player) final override;

	~ADroppedWeapon() = default;
};
