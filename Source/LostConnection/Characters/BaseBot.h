// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Components/MaterialBillboardComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "BaseCharacter.h"
#include "Utility/Utility.h"

#include "BaseBot.generated.h"

UCLASS()
class LOSTCONNECTION_API ABaseBot : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UMaterialBillboardComponent* healthBar;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly)
	UTextRenderComponent* healthBarTextRender;

	UPROPERTY(Category = DynamicMaterials, BlueprintReadOnly)
	UMaterialInstanceDynamic* healthBarMaterial;

	UPROPERTY()
	UMaterialInstance* baseHealthBarMaterial;

protected:
	virtual void onCurrentHealthChanged() override;

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

protected:
	virtual void deathLogic() override;

public:
	ABaseBot();

	virtual void updateHealthBar() final;

	virtual void setHealthBarVisibility(bool isVisible) final;

	virtual UMaterialBillboardComponent* getHealthBar() const;

	virtual UTextRenderComponent* getHealthBarTextRender() const;

	virtual ~ABaseBot() = default;
};

inline void ABaseBot::updateHealthBar()
{
	healthBarMaterial->SetScalarParameterValue("LifePercent", Utility::toPercent(currentHealth / health));

	healthBarTextRender->SetText(Utility::getFTextFromFloat(currentHealth));
}

inline void ABaseBot::setHealthBarVisibility(bool isVisible)
{
	healthBar->SetVisibility(isVisible);

	healthBarTextRender->SetVisibility(isVisible);
}

inline UMaterialBillboardComponent* ABaseBot::getHealthBar() const
{
	return healthBar;
}

inline UTextRenderComponent* ABaseBot::getHealthBarTextRender() const
{
	return healthBarTextRender;
}
