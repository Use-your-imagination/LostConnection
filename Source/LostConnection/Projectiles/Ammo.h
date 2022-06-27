// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Interfaces/Holders/AilmentInflictorHolder.h"

#include "Ammo.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API AAmmo :
	public APawn,
	public IAilmentInflictorHolder
{
	GENERATED_BODY()

private:
	void PostInitializeComponents() override;

private:
	UFUNCTION()
	void onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> mesh;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> visibleMesh;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UNiagaraComponent> tracer;

	UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UProjectileMovementComponent> movement;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMesh> brokenAmmoMeshAsset;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UNiagaraSystem> onHitAsset;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float ammoSpeed;

	UPROPERTY()
	TObjectPtr<UAilmentInflictorUtility> ailmentInflictorUtility;

	TWeakObjectPtr<class ABaseCharacter> owner;
	AActor* lastTarget;
	bool isAlly;

public:
	AAmmo();

	void launch(const TWeakObjectPtr<class ABaseCharacter>& character, const FTransform& visibleAmmoRelativeTransform, const FRotator& spread);

	virtual void copyProperties(TObjectPtr<class UBaseWeapon> weapon);

	TObjectPtr<UStaticMeshComponent> getAmmoMeshComponent() const;

	bool getIsAlly() const;

	const TWeakObjectPtr<class ABaseCharacter>& getOwner() const;

	UAilmentInflictorUtility* getAilmentInflictorUtility() const override;

	~AAmmo() = default;

	friend class AFakeAmmo;
};
