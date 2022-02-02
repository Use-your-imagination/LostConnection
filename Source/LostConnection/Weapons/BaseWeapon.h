// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Animation/AimOffsetBlendSpace.h"
#include "Animation/AnimSequence.h"

#include "Network/NetworkObject.h"
#include "Projectiles/Ammo.h"

#include "BaseWeapon.generated.h"

#pragma warning(disable: 4458)

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
	small = 0 UMETA(DisplayName = "Small ammo"),
	large = 1 UMETA(DisplayName = "Large ammo"),
	energy = 2 UMETA(DisplayName = "Energy ammo"),
	defaultType = 3 UMETA(DisplayName = "Default ammo")
};

UENUM(BlueprintType)
enum class weaponSlotTypes : uint8
{
	none,
	primaryWeaponSlot,
	secondaryWeaponSlot,
	defaultWeaponSlot,
	firstInactiveWeaponSlot,
	secondInactiveWeaponSlot
};

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API UBaseWeapon : public UNetworkObject
{
	GENERATED_BODY()
		
private:
	TWeakObjectPtr<class ABaseCharacter> owner;
	float timeBetweenShots;
	float currentTimeBetweenShots;
	bool isShooting;

private:
	FTransform calculateAmmoTransform(class ABaseDrone* drone, const FTransform& weaponBarrelTransform);

	FTransform calculateVisibleAmmoTransform(class ABaseDrone* drone, const FTransform& weaponBarrelTransform, const FTransform& ammoTransform);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void shoot();

protected:
	UPROPERTY(Category = Components, EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMesh* mesh;

	UPROPERTY(Category = Components, EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* magazineMesh;

	UPROPERTY(Category = "Animations|States|Hip", EditDefaultsOnly, BlueprintReadOnly)
	UAimOffsetBlendSpace* hipAimOffset;

	UPROPERTY(Category = "Animations|States|Hip", EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* hipBasePoseAnimation;

	UPROPERTY(Category = "Animations|States|Hip", EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* hipShootAnimation;

	UPROPERTY(Category = "Animations|States|ADS", EditDefaultsOnly, BlueprintReadOnly)
	UAimOffsetBlendSpace* adsAimOffset;

	UPROPERTY(Category = "Animations|States|ADS", EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* adsBasePoseAnimation;

	UPROPERTY(Category = "Animations|States|ADS", EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* adsShootAnimation;

	UPROPERTY(Category = "Animations|Actions", EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* reloadAnimation;

	UPROPERTY(Category = "Animations|Actions", EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* switchFromAnimation;

	UPROPERTY(Category = "Animations|Actions", EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* switchToAnimation;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	ammoTypes ammoType;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	typeOfDamage damageType;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float damage;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int32 currentMagazineSize;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int32 magazineSize;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int32 ammoCost;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	int32 roundsPerSecond;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	weaponTypes weaponType;

	/*
	* spreadDistance * currentAccuracyMultiplier;
	* pitch = FMath::RandRange(-currentSpreadDistance, currentSpreadDistance);
	* yaw = FMath::Tan(FMath::Acos(pitch / currentSpreadDistance)) * pitch;
	* Rotation = { pitch, FMath::RandRange(-yaw, yaw), 0.0f };
	*/
	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float spreadDistance;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float crushingHitChance;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float length;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AAmmo> ammoClass;

	/*
	* float decreaseAccuracyMultiplier = 0.95f;
	* currentAccuracyMultiplier += drawback;
	* Tick: currentAccuracyMultiplier = FMath::Max(1.0f, currentAccuracyMultiplier * decreaseAccuracyMultiplier);
	*/
	UPROPERTY(Category = Weapons, EditDefaultsOnly, BlueprintReadOnly)
	float drawback;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	float addedDamage;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	float additionalDamage;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	TArray<float> increasedDamageCoefficients;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	TArray<float> moreDamageCoefficients;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	float additionalCrushingHitChance;

	UPROPERTY(Category = Weapons, Replicated, BlueprintReadOnly)
	float currentAccuracyMultiplier;

private:
	UFUNCTION(Category = Weapons, BlueprintCallable, Meta = (AllowPrivateAccess = "true"))
	float calculateSpreadDistance() const;

public:
	UBaseWeapon();

	void startShoot();

	void resetShoot(USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character);

	void alternativeMode();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void updateTimeBetweenShots();

	void Tick(float DeltaTime);

	void appendIncreasedDamageCoefficient(float coefficient);

	void removeIncreasedDamageCoefficient(float coefficient);

	void appendMoreDamageCoefficient(float coefficient);

	void removeMoreDamageCoefficient(float coefficient);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void setOwner(class ABaseCharacter* owner);

	UFUNCTION(Server, Reliable)
	void setAmmoType(ammoTypes newAmmoType);

	UFUNCTION(Server, Reliable)
	void setBaseDamage(float newDamage);

	UFUNCTION(Server, Reliable)
	void setAddedDamage(float newAddedDamage);

	UFUNCTION(Server, Reliable)
	void setAdditionalDamage(float newAdditionalDamage);

	UFUNCTION(Server, Reliable)
	void setCurrentMagazineSize(int32 newCurrentMagazineSize);

	UFUNCTION(Server, Reliable)
	void setRateOfFire(int32 newRoundsPerSecond);

	UFUNCTION(Server, Reliable)
	void setWeaponType(weaponTypes newWeaponType);

	USkeletalMesh* getWeaponMesh() const;

	UStaticMesh* getMagazineMesh() const;

	ammoTypes getAmmoType() const;

	typeOfDamage getDamageType() const;

	float getBaseDamage() const;

	float getAddedDamage() const;

	float getAdditionalDamage() const;

	int32 getCurrentMagazineSize() const;

	int32 getMagazineSize() const;

	int32 getRoundsPerSecond() const;

	weaponTypes getWeaponType() const;

	const TWeakObjectPtr<class ABaseCharacter>& getOwner() const;

	float getCrushingHitChance() const;

	float getAdditionalCrushingHitChance() const;

	float getLength() const;

	virtual ~UBaseWeapon() = default;
};

inline float UBaseWeapon::calculateSpreadDistance() const
{
	return spreadDistance * currentAccuracyMultiplier;
}
