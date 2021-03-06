// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

#include "Characters/BaseDrone.h"
#include "WorldPlaceables/DroppedObject.h"
#include "Utility/Enums.h"

#include "BaseDroppedAmmo.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API ABaseDroppedAmmo : public ADroppedObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UBoxComponent> collisionBox;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<USphereComponent> pickupArea;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMesh> mid;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMesh> empty;

	UPROPERTY(Category = Stats, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 amount;

	UPROPERTY(Category = Stats, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	EAmmoType type;

	UPROPERTY(Category = Stats, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float lifetime;

	TWeakObjectPtr<ABaseDrone> drone;
	int32 currentAmount;

private:
	UFUNCTION()
	void onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void onEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void pickup();

	void PostInitializeComponents() override;

public:
	ABaseDroppedAmmo();

	void Tick(float DeltaSeconds) override;

	virtual ~ABaseDroppedAmmo() = default;
};
