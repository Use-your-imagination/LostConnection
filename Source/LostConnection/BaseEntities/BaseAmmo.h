#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "../Interfaces/ShotThrough.h"

#include "BaseAmmo.generated.h"

#define GET_STATIC_CLASS_OVERRIDE(className) inline UClass* getStaticClass() const override \
{ \
	return className::StaticClass(); \
}

UENUM(BlueprintType)
enum class ammoType : uint8
{
	large = 0 UMETA(DisplayName = "Large ammo"),
	small = 1 UMETA(DisplayName = "Small ammo"),
	energy = 2 UMETA(DisplayName = "Energy ammo"),
	defaultType = 3 UMETA(DisplayName = "Default ammo")
};

UCLASS()
class LOSTCONNECTION_API ABaseAmmo :
	public APawn,
	public IShotThrough
{
	GENERATED_BODY()

protected:
	virtual void Tick(float deltaSeconds) override;

	UFUNCTION()
	void beginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void endOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* mesh;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadWrite)
	float damage;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadWrite)
	float speed;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadWrite)
	ammoType type;

public:
	ABaseAmmo();

	virtual UClass* getStaticClass() const;

	virtual void setAmmoMesh(UStaticMesh* mesh) final;

	virtual void setDamage(float damage) final;

	virtual void setAmmoSpeed(float speed) final;

	virtual UStaticMeshComponent* getAmmoMesh() const final;

	virtual float getDamage() const final;

	virtual float getSpeed() const final;

	virtual ammoType getAmmoType() const final;

	float getFlatDamageReduction_Implementation() const override;

	float getPercentageDamageReduction_Implementation() const override;

	virtual ~ABaseAmmo() = default;
};
