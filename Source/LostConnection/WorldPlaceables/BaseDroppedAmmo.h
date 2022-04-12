// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"

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
	TObjectPtr<USphereComponent> pickupArea;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh> mid;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh> empty;

	UPROPERTY(Category = Stats, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 amount;

	UPROPERTY(Category = Stats, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	EAmmoType type;

	int32 currentAmount;

private:
	void onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void pickup(TObjectPtr<ABaseDrone> drone);

	void PostInitializeComponents() override;

public:
	ABaseDroppedAmmo();

	virtual ~ABaseDroppedAmmo() = default;
};
