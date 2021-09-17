#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "BaseAmmo.generated.h"

#define GET_STATIC_CLASS_OVERRIDE(className) inline UClass* getStaticClass() const override \
{ \
	return className::StaticClass(); \
}

UENUM(BlueprintType)
enum class ammoTypes : uint8
{
	large = 0 UMETA(DisplayName = "Large ammo"),
	small = 1 UMETA(DisplayName = "Small ammo"),
	energy = 2 UMETA(DisplayName = "Energy ammo"),
	defaultType = 3 UMETA(DisplayName = "Default ammo")
};

UCLASS()
class LOSTCONNECTION_API ABaseAmmo : public APawn
{
	GENERATED_BODY()

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

private:
	ACharacter* lastTarget;

	UPROPERTY(Replicated)
	bool isAlly;

protected:
	UFUNCTION()
	void beginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* mesh;

	UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadWrite, Replicated)
	UProjectileMovementComponent* movement;
	
	UPROPERTY(Category = Particles, VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* tracer;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UStaticMesh* brokenAmmoMesh;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadWrite)
	float damage;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadWrite)
	ammoTypes ammoType;

public:
	ABaseAmmo();

	virtual void launch(ACharacter* character) final;

	virtual void copyProperties(ABaseAmmo* other);

	virtual UClass* getStaticClass() const;

	virtual void setAmmoMesh(UStaticMesh* mesh) final;

	virtual void setDamage(float damage) final;

	virtual void setAmmoSpeed(float speed) final;

	virtual UStaticMeshComponent* getAmmoMeshComponent() const final;

	UFUNCTION(BlueprintCallable)
	virtual float getDamage() const final;

	UFUNCTION(BlueprintCallable)
	virtual float getSpeed() const final;

	UFUNCTION(BlueprintCallable)
	virtual ammoTypes getAmmoType() const final;

	virtual ~ABaseAmmo() = default;
};
