// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "DroppedObject.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API ADroppedObject : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* mesh;

	UPROPERTY(Category = Particles, VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* vfx;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	
	ADroppedObject();

	virtual void setMesh(USkeletalMesh* mesh);

	virtual ~ADroppedObject() = default;
};
