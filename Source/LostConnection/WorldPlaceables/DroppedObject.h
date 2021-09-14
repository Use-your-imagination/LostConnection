// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

#include "Interfaces/Gameplay/Actionable.h"

#include "DroppedObject.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API ADroppedObject :
	public AActor,
	public IActionable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* mesh;

	UPROPERTY(Category = Particles, VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* vfx;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:	
	ADroppedObject();

	virtual void setMesh(USkeletalMesh* mesh);

	virtual void action(AActor* player) override;

	virtual ~ADroppedObject() = default;
};
