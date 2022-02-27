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
	UMaterial* baseHealthBarMaterial;

protected:
	virtual void onHealthChange() override;

	virtual void onCurrentHealthChange() override;

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

protected:
	virtual void deathLogic() override;

public:
	ABaseBot();

	void updateShield();

	void updateHealthBar();

	void setHealthBarVisibility(bool isVisible);

	UMaterialBillboardComponent* getHealthBar() const;

	UTextRenderComponent* getHealthBarTextRender() const;

	virtual ~ABaseBot() = default;
};

FORCEINLINE void ABaseBot::updateHealthBar()
{
	healthBarMaterial->SetScalarParameterValue("LifePercent", Utility::toPercent(currentHealth / health));

	if (IsValid(energyShield))
	{
		healthBarMaterial->SetScalarParameterValue("ShieldPercent", Utility::toPercent(energyShield->getCurrentCapacity() / energyShield->getCapacity()));

		healthBarTextRender->SetText
		(
			FText::Format
			(
				FText::FromString("{0} | {1}"),
				Utility::getFTextFromFloat(energyShield->getCurrentCapacity()),
				Utility::getFTextFromFloat(currentHealth)
			)
		);
	}
	else
	{
		healthBarTextRender->SetText(Utility::getFTextFromFloat(currentHealth));
	}
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
