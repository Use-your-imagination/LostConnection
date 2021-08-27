// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DroppedObject.h"
#include "BaseEntities/BaseWeapon.h"

#include "DroppedWeapon.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ADroppedWeapon :
	public ADroppedObject
{
	GENERATED_BODY()

private:
	UBaseWeapon* weapon;

protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* magazine;

public:
	ADroppedWeapon();

	void setWeapon(UBaseWeapon* weapon);

	void action(AActor* player) final override;

	~ADroppedWeapon() = default;
};
