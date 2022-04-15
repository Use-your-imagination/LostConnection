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
	UFUNCTION()
	void onWeaponChange();

	virtual void Tick(float DeltaTime) final override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	virtual void action(TObjectPtr<class ABaseDrone> player) final override;

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

	~ADroppedWeapon() = default;
};
