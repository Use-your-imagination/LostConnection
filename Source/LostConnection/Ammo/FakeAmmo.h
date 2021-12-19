// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "BaseAmmo.h"

#include "FakeAmmo.generated.h"

UCLASS()
class LOSTCONNECTION_API AFakeAmmo : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

	UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* movement;

	UPROPERTY(Category = Particles, VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* tracer;

	UPROPERTY(Category = Components, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UStaticMesh* brokenAmmoMesh;

public:	
	AFakeAmmo();
	
	void copyAmmo(ABaseAmmo* ammo);

	void deactivateTracer();

	UStaticMeshComponent* getFakeAmmoMeshComponent() const;

	~AFakeAmmo() = default;
};
