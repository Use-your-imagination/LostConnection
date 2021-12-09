// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Interfaces/Gameplay/Statuses/Base/AilmentInflictor.h"

#include "BaseAmmo.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API ABaseAmmo :
	public APawn,
	public IAilmentInflictor
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
	UNiagaraSystem* tracerAsset;

	UPROPERTY(Category = Components, BlueprintReadOnly)
	UStaticMesh* brokenAmmoMesh;

	UPROPERTY(Category = Particles, BlueprintReadOnly)
	UNiagaraSystem* onHitAsset;

	UPROPERTY()
	class AFakeAmmo* fakeAmmo;

	AActor* lastTarget;
	float damage;
	float additionalDamage;
	typeOfDamage damageType;
	bool isAlly;
	float crushingHitChance;
	float additionalCrushingHitChance;

public:
	ABaseAmmo();

	UFUNCTION(NetMulticast, Reliable)
	virtual void launch(class ABaseCharacter* character, const FTransform& fakeAmmoTransform, const FRotator& spread) final;

	virtual void copyProperties(class UBaseWeapon* weapon);

	virtual UStaticMeshComponent* getAmmoMeshComponent() const final;

	virtual bool getIsAlly() const final;

	virtual const TWeakObjectPtr<class ABaseCharacter>& getOwnerCharacter() const final;

	UFUNCTION(Server, Reliable)
	virtual void setInflictorDamage(float newDamage) final override;

	UFUNCTION(Server, Reliable)
	virtual void setAdditionalInflictorDamage(float newAdditionalDamage) final override;

	UFUNCTION(Server, Reliable)
	virtual void setCrushingHitChance(float newCrushingHitChance) final override;

	UFUNCTION(Server, Reliable)
	virtual void setAdditionalCrushingHitChance(float newAdditionalCrushingHitChance) final override;

	virtual float getInflictorDamage() const final override;

	virtual float getAdditionalInflictorDamage() const final override;

	virtual typeOfDamage getDamageType() const final override;

	virtual float getCrushingHitChance() const final override;

	virtual float getAdditionalCrushingHitChance() const final override;

	virtual ~ABaseAmmo() = default;

	friend class AFakeAmmo;
};
