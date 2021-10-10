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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	virtual void shoot(USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character);

protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	USkeletalMesh* mesh;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UStaticMesh* magazineMesh;

	UPROPERTY(Category = Weapons, VisibleAnywhere, Replicated, BlueprintReadOnly)
	ABaseAmmo* ammo;

	UPROPERTY(Category = Weapons, VisibleAnywhere, Replicated, BlueprintReadOnly)
	int currentMagazineSize;

	UPROPERTY(Category = Weapons, VisibleAnywhere, Replicated, BlueprintReadOnly)
	int magazineSize;

	UPROPERTY(Category = Weapons, VisibleAnywhere, Replicated, BlueprintReadOnly)
	int ammoCost;

	UPROPERTY(Category = Weapons, VisibleAnywhere, Replicated, BlueprintReadOnly)
	int roundsPerSecond;

	UPROPERTY(Category = Weapons, VisibleAnywhere, Replicated, BlueprintReadOnly)
	weaponTypes weaponType;

	UPROPERTY(Category = Weapons, VisibleAnywhere, Replicated, BlueprintReadOnly)
	float spreadDistance;

public:
	ABaseWeapon();

	virtual void shoot(UWorld* world, USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character) final;

	virtual void resetShoot(UWorld* world, USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character) final;

	virtual void alternativeMode();

	UFUNCTION(Server, Reliable)
	virtual void reduceShootRemainigTime(float deltaSeconds);

	UFUNCTION(Server, Reliable)
	virtual void setCurrentMagazineSize(int newCurrentMagazineSize) final;

	UFUNCTION(Server, Reliable)
	virtual void setRateOfFire(int newRoundsPerSecond) final;

	UFUNCTION(Server, Reliable)
	virtual void setWeaponType(weaponTypes newWeaponType) final;

	virtual USkeletalMesh* getWeaponMesh() const final;

	virtual UStaticMesh* getMagazineMesh() const final;

	virtual ABaseAmmo* getAmmo() const final;

	virtual int getCurrentMagazineSize() const final;

	virtual int getMagazineSize() const final;

	virtual int getRoundsPerSecond() const final;

	virtual weaponTypes getWeaponType() const final;

	virtual ~ABaseWeapon() = default;
};
