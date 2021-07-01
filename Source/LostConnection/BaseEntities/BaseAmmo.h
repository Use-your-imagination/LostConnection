#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "BaseAmmo.generated.h"

#define GET_STATIC_CLASS_OVERRIDE(className) inline UClass* getStaticClass() const override \
{ \
	return className::StaticClass(); \
}

UCLASS()
class LOSTCONNECTION_API ABaseAmmo : public APawn
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

public:
	ABaseAmmo();

	virtual UClass* getStaticClass() const;

	virtual void setAmmoMesh(UStaticMesh* mesh) final;

	virtual void setDamage(float damage) final;

	virtual void setAmmoSpeed(float speed) final;

	virtual UStaticMeshComponent* getAmmoMesh() const final;

	virtual ~ABaseAmmo() = default;
};
