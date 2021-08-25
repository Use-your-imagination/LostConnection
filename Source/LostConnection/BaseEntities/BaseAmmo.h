#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"

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
class LOSTCONNECTION_API ABaseAmmo :
	public APawn
{
	GENERATED_BODY()

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	ACharacter* lastTarget;

	UPROPERTY(Replicated)
	bool isAlly;

protected:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void beginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void endOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* mesh;

	UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* movement;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* collision;
	
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

	void launch(ACharacter* character);

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
