// Copyright (c) 2021 Use-your-imagination

#include "BaseBot.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Font.h"

#include "Weapons/Pistols/Gauss.h"

void ABaseBot::onCurrentHealthChanged()
{
	if (currentHealth != health)
	{
		this->setHealthBarVisibility(true);

		this->updateHealthBar();
	}
	else
	{
		this->setHealthBarVisibility(false);
	}
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

	healthBarTextRender->SetText(Utility::getFTextFromFloat(currentHealth));

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

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	healthBar = CreateDefaultSubobject<UMaterialBillboardComponent>(TEXT("HealthBar"));
	healthBarTextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("healthBarTextRender"));
	
	healthBar->SetupAttachment(GetMesh());

	healthBarTextRender->SetupAttachment(healthBar);

	healthBar->AddRelativeLocation(FVector(0.0f, 0.0f, 187.0f));

	healthBarTextRender->SetTextMaterial(textMaterialFinder.Object);

	healthBarTextRender->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	healthBarTextRender->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	healthBarTextRender->SetTextRenderColor(FColor::White);
	healthBarTextRender->SetFont(textFontFinder.Object);

	baseHealthBarMaterial = healthBarBaseMaterialFinder.Object;

	healthBar->SetVisibility(false);

	healthBarTextRender->SetVisibility(false);
}
