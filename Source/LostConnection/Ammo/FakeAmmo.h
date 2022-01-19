// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "BaseAmmo.h"

#include "FakeAmmo.generated.h"

UCLASS(BlueprintType, DefaultToInstanced)
class LOSTCONNECTION_API AFakeAmmo : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Components, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

	UPROPERTY(Category = Movement, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* movement;

	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* tracer;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float ammoSpeed;

public:	
	AFakeAmmo();
	
	UStaticMeshComponent* getFakeAmmoMeshComponent() const;

	~AFakeAmmo() = default;
};
