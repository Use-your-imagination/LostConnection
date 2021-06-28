#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "BaseWeapon.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

public:
	ABaseWeapon();

	virtual UStaticMesh* getWeaponMesh() const final;

	virtual ~ABaseWeapon() = default;
};
