#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "BaseAmmo.h"

#include "BaseWeapon.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* mesh;

	ABaseAmmo* ammo;

public:
	ABaseWeapon();

	virtual USkeletalMesh* getWeaponMesh() const final;

	virtual void fire();

	virtual ~ABaseWeapon() = default;
};
