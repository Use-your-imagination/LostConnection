// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

#include "DropppedObject.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API ADropppedObject :
	public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* collisionBox;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* mesh;

	UPROPERTY(Category = Particles, VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* vfx;

protected:
	virtual void BeginPlay() override;

public:	
	ADropppedObject();

	virtual void setMesh(USkeletalMesh* mesh) final;

	virtual ~ADropppedObject() = default;
};
