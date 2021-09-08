#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "BaseAmmo.h"

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
class LOSTCONNECTION_API UBaseWeapon :
	public UObject
{
	GENERATED_BODY()

protected:
	virtual bool IsSupportedForNetworking() const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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

	int rateOfFire;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadWrite)
	weaponTypes weaponType;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadWrite)
	float spreadDistance;

public:
	UBaseWeapon();

	virtual void shoot(USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character);

	virtual void alternativeMode();

	virtual void setCurrentMagazineSize(int currentMagazineSize) final;

	virtual void setRateOfFire(int rateOfFire) final;

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

	virtual ~UBaseWeapon() = default;
};
