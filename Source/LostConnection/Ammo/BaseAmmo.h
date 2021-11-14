#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Statuses/BaseStatus.h"

#include "BaseAmmo.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API ABaseAmmo :
	public APawn,
	public IStatusInflictor
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<class ABaseCharacter> ownerCharacter;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

protected:
	UFUNCTION()
	void onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(Category = Components, BlueprintReadOnly)
	UStaticMeshComponent* mesh;

	UPROPERTY(Category = Movement, Replicated, BlueprintReadOnly)
	UProjectileMovementComponent* movement;
	
	UPROPERTY(Category = Particles, BlueprintReadOnly)
	UNiagaraComponent* tracer;

	UPROPERTY(Category = Components, BlueprintReadOnly)
	UStaticMesh* brokenAmmoMesh;

	UPROPERTY(Category = Particles, BlueprintReadOnly)
	UNiagaraSystem* onHitAsset;

	AActor* lastTarget;
	float damage;
	typeOfDamage damageType;
	bool isAlly;
	float crushingHitChance;

public:
	ABaseAmmo();

	virtual void launch(class ABaseCharacter* character) final;

	virtual void copyProperties(class UBaseWeapon* weapon);

	virtual UStaticMeshComponent* getAmmoMeshComponent() const final;

	virtual float getDamage() const final;

	virtual bool getIsAlly() const final;

	virtual const TWeakObjectPtr<class ABaseCharacter>& getOwnerCharacter() const final;

	virtual float getInflictorDamage() const final override;

	virtual typeOfDamage getDamageType() const final override;

	virtual bool getCrushingHitProc() const override;

	virtual ~ABaseAmmo() = default;
};
