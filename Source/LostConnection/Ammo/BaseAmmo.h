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

UCLASS(BlueprintType)
class LOSTCONNECTION_API ABaseAmmo : public APawn
{
	GENERATED_BODY()

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* mesh;

	UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadWrite, Replicated)
	UProjectileMovementComponent* movement;
	
	UPROPERTY(Category = Particles, VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* tracer;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UStaticMesh* brokenAmmoMesh;

	UPROPERTY(Category = Particles, VisibleAnywhere, BlueprintReadOnly)
	UNiagaraSystem* onHitAsset;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadOnly, Replicated)
	float damage;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadOnly, Replicated)
	ammoTypes ammoType;

	UPROPERTY(Category = AmmoSettings, VisibleAnywhere, BlueprintReadOnly, Replicated)
	bool isAlly;

	AActor* lastTarget;

private:
	UFUNCTION(NetMulticast, Reliable)
	void setAmmoMeshMulticast(UStaticMesh* newMesh);

public:
	ABaseAmmo();

	virtual void launch(class ABaseCharacter* character) final;

	virtual void copyProperties(ABaseAmmo* other);

	virtual UClass* getStaticClass() const;

	UFUNCTION(Server, Reliable)
	virtual void setAmmoMesh(UStaticMesh* newMesh) final;

	UFUNCTION(Server, Reliable)
	virtual void setDamage(float newDamage) final;

	UFUNCTION(Server, Reliable)
	virtual void setAmmoSpeed(float speed) final;

	UFUNCTION(Server, Reliable)
	virtual void setAmmoType(ammoTypes newAmmoType) final;

	virtual UStaticMeshComponent* getAmmoMeshComponent() const final;

	virtual float getDamage() const final;

	UFUNCTION(BlueprintCallable)
	virtual float getSpeed() const final;

	virtual ammoTypes getAmmoType() const final;

	virtual bool getIsAlly() const final;

	virtual ~ABaseAmmo() = default;
};
