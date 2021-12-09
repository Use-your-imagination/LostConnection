// Copyright (c) 2021 Use-your-imagination

#include "BaseBot.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Font.h"

#include "Utility/Utility.h"
#include "Weapons/Pistols/Gauss.h"

void ABaseBot::updateHealthBar_Implementation(float updatedCurrentHealth, float maxHealth)
{
	healthBarMaterial->SetScalarParameterValue(TEXT("LifePercent"), (updatedCurrentHealth / maxHealth) * 100.0f);

	healthBarText->SetText(Utility::getFTextFromFloat(updatedCurrentHealth));
}

void ABaseBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseBot::BeginPlay()
{
	Super::BeginPlay();

	healthBarMaterial = UMaterialInstanceDynamic::Create(baseHealthBarMaterial, this);

	healthBar->AddElement(healthBarMaterial, nullptr, false, 10.0f, 40.0f, nullptr);

	healthBarText->SetText(Utility::getFTextFromFloat(currentHealth));

	if (HasAuthority())
	{
		this->setDefaultWeapon(ULostConnectionAssetManager::get().getWeaponClass(UGauss::StaticClass()));

		this->changeToDefaultWeapon();
	}
}

void ABaseBot::deathLogic()
{
	Destroy();
}

ABaseBot::ABaseBot()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> healthBarBaseMaterialFinder(TEXT("MaterialInstanceConstant'/Game/Assets/FX/M_HealthBar_Inst.M_HealthBar_Inst'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> textMaterialFinder(TEXT("Material'/Game/Assets/FX/M_NumericLife.M_NumericLife'"));
	static ConstructorHelpers::FObjectFinder<UFont> textFontFinder(TEXT("Font'/Engine/EditorResources/SmallFont.SmallFont'"));
	
	isAlly = false;

	healthBar = CreateDefaultSubobject<UMaterialBillboardComponent>(TEXT("HealthBar"));
	healthBarText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthBarText"));
	
	healthBar->SetupAttachment(GetMesh());

	healthBarText->SetupAttachment(healthBar);

	healthBar->AddRelativeLocation(FVector(0.0f, 0.0f, 187.0f));

	healthBarText->SetTextMaterial(textMaterialFinder.Object);

	healthBarText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	healthBarText->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	healthBarText->SetTextRenderColor(FColor::White);
	healthBarText->SetFont(textFontFinder.Object);

	baseHealthBarMaterial = healthBarBaseMaterialFinder.Object;
}

void ABaseBot::setCurrentHealth_Implementation(float newCurrentHealth)
{
	Super::setCurrentHealth_Implementation(newCurrentHealth);

	this->updateHealthBar(currentHealth, health);
}
