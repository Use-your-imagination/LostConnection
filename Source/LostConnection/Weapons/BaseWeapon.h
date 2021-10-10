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

UCLASS()
class LOSTCONNECTION_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
		
private:
	FTimerHandle shootHandle;
	float shootRemainingTime;
	bool clearTimer;

protected:
	virtual bool IsSupportedForNetworking() const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void shoot(USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character);

protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	USkeletalMesh* mesh;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UStaticMesh* magazineMesh;

	UPROPERTY(Category = Weapons, VisibleAnywhere, BlueprintReadWrite)
	ABaseAmmo* ammo;

	UPROPERTY(Replicated)
	int currentMagazineSize;

	UPROPERTY(Replicated)
	int magazineSize;

	int ammoCost;

	int roundsPerSecond;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadWrite, Replicated)
	weaponTypes weaponType;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadWrite)
	float spreadDistance;

public:
	ABaseWeapon();

	virtual void shoot(UWorld* world, USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character) final;

	virtual void resetShoot(UWorld* world, USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character) final;

	virtual void alternativeMode();

	UFUNCTION(Server, Reliable)
	virtual void reduceShootRemainigTime(float deltaSeconds);

	virtual void setCurrentMagazineSize(int currentMagazineSize) final;

	virtual void setRateOfFire(int roundsPerSecond) final;

	virtual void setWeaponType(weaponTypes weaponType) final;

	virtual USkeletalMesh* getWeaponMesh() const final;

	virtual UStaticMesh* getMagazineMesh() const final;

	virtual ABaseAmmo* getAmmo() const final;

	UFUNCTION(BlueprintCallable)
	virtual int getCurrentMagazineSize() const final;

	UFUNCTION(BlueprintCallable)
	virtual int getMagazineSize() const final;

	UFUNCTION(BlueprintCallable)
	virtual int getRateOfFire() const final;

	UFUNCTION(BlueprintCallable)
	virtual weaponTypes getWeaponType() const final;

	virtual ~ABaseWeapon() = default;
};
