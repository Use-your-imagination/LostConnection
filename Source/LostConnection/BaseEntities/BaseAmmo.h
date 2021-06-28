#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "BaseAmmo.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseAmmo : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

public:
	ABaseAmmo();

	virtual void setAmmoMesh(UStaticMesh* mesh) final;

	virtual ~ABaseAmmo() = default;
};
