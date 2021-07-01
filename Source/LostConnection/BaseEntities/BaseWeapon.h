#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "BaseAmmo.h"
#include "../Interfaces/ShotThrough.h"

#include "BaseWeapon.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseWeapon :
	public AActor,
	public IShotThrough
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* mesh;

	UPROPERTY()
	ABaseAmmo* ammo;

public:
	ACharacter* character;

public:
	ABaseWeapon();

	virtual void shoot(USkeletalMeshComponent* currentVisibleWeaponMesh);

	virtual USkeletalMesh* getWeaponMesh() const final;

	float getFlatDamageReduction_Implementation() const override;

	float getPercentageDamageReduction_Implementation() const override;

	virtual ~ABaseWeapon() = default;
};
