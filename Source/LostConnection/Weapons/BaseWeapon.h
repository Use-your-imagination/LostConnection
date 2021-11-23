// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

#include "Ammo/BaseAmmo.h"

#include "BaseWeapon.generated.h"

UENUM(BlueprintType)
enum class weaponTypes : uint8
{
	automatic = 0 UMETA(DisplayName = "Automatic"),
	semiAutomatic = 1 UMETA(DisplayName = "Semi-automatic"),
	single = 2 UMETA(DisplayName = "Single"),
	delay = 3 UMETA(DisplayName = "Delay")
};

UENUM(BlueprintType)
enum class ammoTypes : uint8
{
	large = 0 UMETA(DisplayName = "Large ammo"),
	small = 1 UMETA(DisplayName = "Small ammo"),
	energy = 2 UMETA(DisplayName = "Energy ammo"),
	defaultType = 3 UMETA(DisplayName = "Default ammo")
};

UCLASS()
class LOSTCONNECTION_API UBaseWeapon : public UObject
{
	GENERATED_BODY()
		
private:
	UWorld* world;
	TWeakObjectPtr<class ABaseCharacter> ownerCharacter;
	float timeBetweenShots;
	float currentTimeBetweenShots;
	bool isShooting;

protected:
	virtual bool IsSupportedForNetworking() const final override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void shoot();

protected:
	UPROPERTY(Category = Components, BlueprintReadOnly)
	USkeletalMesh* mesh;

	UPROPERTY(Category = Components, BlueprintReadOnly)
	UStaticMesh* magazineMesh;

	UPROPERTY()
	UClass* animationBlueprint;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	ammoTypes ammoType;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	typeOfDamage damageType;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	float damage;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	int currentMagazineSize;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	int magazineSize;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	int ammoCost;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	int roundsPerSecond;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	weaponTypes weaponType;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	float spreadDistance;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	float crushingHitChance;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	float additionalCrushingHitChance;

	UClass* ammoClass;

public:
	UBaseWeapon();

	virtual void startShoot() final;

	virtual void resetShoot(UWorld* world, USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character) final;

	virtual void alternativeMode();

	UFUNCTION(Server, Reliable)
	virtual void updateTimeBetweenShots() final;

	virtual void Tick(float DeltaTime);

	virtual void setWorld(UWorld* world) final;

	virtual void setOwnerCharacter(class ABaseCharacter* ownerCharacter) final;

	UFUNCTION(Server, Reliable)
	virtual void setAmmoType(ammoTypes newAmmoType) final;

	UFUNCTION(Server, Reliable)
	virtual void setDamage(float newDamage) final;

	UFUNCTION(Server, Reliable)
	virtual void setCurrentMagazineSize(int newCurrentMagazineSize) final;

	UFUNCTION(Server, Reliable)
	virtual void setRateOfFire(int newRoundsPerSecond) final;

	UFUNCTION(Server, Reliable)
	virtual void setWeaponType(weaponTypes newWeaponType) final;

	virtual USkeletalMesh* getWeaponMesh() const final;

	virtual UStaticMesh* getMagazineMesh() const final;

	virtual ammoTypes getAmmoType() const final;

	virtual typeOfDamage getDamageType() const final;

	virtual float getDamage() const final;

	virtual int getCurrentMagazineSize() const final;

	virtual int getMagazineSize() const final;

	virtual int getRoundsPerSecond() const final;

	virtual weaponTypes getWeaponType() const final;

	virtual UClass* getAnimationBlueprint() const final;

	virtual const TWeakObjectPtr<class ABaseCharacter>& getOwnerCharacter() const final;

	virtual float getCrushingHitChance() const final;

	virtual float getAdditionalCrushingHitChance() const final;

	virtual ~UBaseWeapon() = default;
};
