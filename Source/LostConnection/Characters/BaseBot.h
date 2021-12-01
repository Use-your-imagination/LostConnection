// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Components/MaterialBillboardComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "BaseCharacter.h"

#include "BaseBot.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseBot : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UMaterialBillboardComponent* healthBar;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UTextRenderComponent* healthBarText;

	UPROPERTY(Category = DynamicMaterials, BlueprintReadOnly)
	UMaterialInstanceDynamic* healthBarMaterial;

	UPROPERTY()
	UMaterialInstance* baseHealthBarMaterial;

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

protected:
	virtual void deathLogic() override;

public:
	ABaseBot();

	virtual void setCurrentHealth_Implementation(float newCurrentHealth) override;

	virtual ~ABaseBot() = default;
};
