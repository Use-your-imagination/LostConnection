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

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ABaseAmmo* ammo;

	int currentMagazineSize;

	int magazineSize;

	int ammoCost;

public:
	ACharacter* character;

public:
	ABaseWeapon();

	virtual bool shoot(USkeletalMeshComponent* currentVisibleWeaponMesh);

	virtual void setCurrentMagazineSize(int currentMagazineSize) final;

	virtual USkeletalMesh* getWeaponMesh() const final;

	virtual ABaseAmmo* getAmmo() const final;

	UFUNCTION(BlueprintCallable)
	virtual int getCurrentMagazineSize() const final;

	UFUNCTION(BlueprintCallable)
	virtual int getMagazineSize() const final;

	float getFlatDamageReduction_Implementation() const override;

	float getPercentageDamageReduction_Implementation() const override;

	virtual ~ABaseWeapon() = default;
};
