// Copyright (c) 2021 Use-your-imagination

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
	
	template<typename ImplementsModuleInterface, typename ModuleInterface, typename ModuleT>
	void applyModules(const TArray<ModuleT*>& modules);

private:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* visibleMesh;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* tracer;

	UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* movement;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UStaticMesh* brokenAmmoMeshAsset;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* onHitAsset;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float ammoSpeed;

	TWeakObjectPtr<class ABaseCharacter> owner;
	AActor* lastTarget;
	UAilmentInflictorUtility* ailmentInflictorUtility;
	bool isAlly;

public:
	AAmmo();

	void launch(const TWeakObjectPtr<class ABaseCharacter>& character, const FTransform& visibleAmmoRelativeTransform, const FRotator& spread);

	virtual void copyProperties(class UBaseWeapon* weapon);

	UStaticMeshComponent* getAmmoMeshComponent() const;

	bool getIsAlly() const;

	const TWeakObjectPtr<class ABaseCharacter>& getOwner() const;

	UAilmentInflictorUtility* getAilmentInflictorUtility() const override;

	virtual ~AAmmo() = default;

	friend class AFakeAmmo;
};
