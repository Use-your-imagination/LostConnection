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

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API UBaseWeapon : public UObject
{
	GENERATED_BODY()
		
private:
	TWeakObjectPtr<class ABaseCharacter> ownerCharacter;
	float timeBetweenShots;
	float currentTimeBetweenShots;
	bool isShooting;

protected:
	virtual bool IsSupportedForNetworking() const final override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void shoot();

protected:
	UPROPERTY(Category = Components, EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMesh* mesh;

	UPROPERTY(Category = Components, EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* magazineMesh;

	UPROPERTY(Category = Animations, EditDefaultsOnly)
	TSubclassOf<UAnimInstance> animationBlueprint;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	ammoTypes ammoType;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	typeOfDamage damageType;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float damage;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	float additionalDamage;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int currentMagazineSize;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int magazineSize;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int ammoCost;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int roundsPerSecond;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	weaponTypes weaponType;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float spreadDistance;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float crushingHitChance;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	float additionalCrushingHitChance;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float length;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ABaseAmmo> ammoClass;

public:
	UBaseWeapon();

	virtual void startShoot() final;

	virtual void resetShoot(USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character) final;

	virtual void alternativeMode();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void updateTimeBetweenShots() final;

	virtual void Tick(float DeltaTime);

	virtual void increaseAdditionalDamage(float amount) final;
	
	virtual void decreaseAdditionalDamage(float amount) final;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void setOwnerCharacter(class ABaseCharacter* ownerCharacter) final;

	UFUNCTION(Server, Reliable)
	virtual void setAmmoType(ammoTypes newAmmoType) final;

	UFUNCTION(Server, Reliable)
	virtual void setDamage(float newDamage) final;

	UFUNCTION(Server, Reliable)
	virtual void setAdditionalDamage(float newAdditionalDamage) final;

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

	virtual float getAdditionalDamage() const final;

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
