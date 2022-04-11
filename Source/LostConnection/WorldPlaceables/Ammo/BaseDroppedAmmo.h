// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"

#include "WorldPlaceables/DroppedObject.h"

#include "BaseDroppedAmmo.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API ABaseDroppedAmmo : public ADroppedObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Assets, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> pickupArea;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh> full;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh> mid;

	UPROPERTY(Category = Assets, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh> empty;

public:
	ABaseDroppedAmmo();

	virtual ~ABaseDroppedAmmo() = default;
};
