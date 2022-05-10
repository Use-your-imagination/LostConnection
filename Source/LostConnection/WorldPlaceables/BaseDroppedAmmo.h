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
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> collisionBox;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> pickupArea;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh> mid;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh> empty;

	UPROPERTY(Category = Stats, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 amount;

	UPROPERTY(Category = Stats, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	EAmmoType type;

	UPROPERTY(Category = Stats, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
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

	void Tick(float DeltaTime) override;

	virtual ~ABaseDroppedAmmo() = default;
};
