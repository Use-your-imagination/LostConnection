// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

#include "Network/NetworkObject.h"
#include "Ammo/BaseAmmo.h"

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

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API UBaseWeapon : public UNetworkObject
{
	GENERATED_BODY()
		
private:
	TWeakObjectPtr<class ABaseCharacter> owner;
	float timeBetweenShots;
	float currentTimeBetweenShots;
	bool isShooting;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void shoot();

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

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float spreadDistance;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float crushingHitChance;

	UPROPERTY(Category = Weapons, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float length;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ABaseAmmo> ammoClass;

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

	UClass* getAnimationBlueprint() const;

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
