// Copyright (c) 2021 Use-your-imagination

#include "BaseBot.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Font.h"

#include "Weapons/Pistols/Gauss.h"
#include "Engine/LostConnectionGameMode.h"
#include "Statuses/Ailments/SwarmAilment.h"

void ABaseBot::onHealthChange()
{
	Super::onHealthChange();

	if (IsValid(healthBarMaterial) && IsValid(energyShield))
	{
		healthBarMaterial->SetScalarParameterValue("LifeToShieldMultiplier", health / energyShield->getCapacity());
	}
}

void ABaseBot::onCurrentHealthChange()
{
	Super::onCurrentHealthChange();

	if (this->isDamaged())
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

	if (HasAuthority())
	{
		this->changeToDefaultWeapon();

		this->updateShield();
	}
}

void ABaseBot::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	healthBarMaterial = UMaterialInstanceDynamic::Create(baseHealthBarMaterial, this);

	healthBar->AddElement(healthBarMaterial, nullptr, false, 10.0f, 40.0f, nullptr);

	healthBarTextRender->SetText(Utility::getFTextFromFloat(currentHealth));
}

void ABaseBot::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseBot, lootPointsReward);
}

void ABaseBot::deathLogic()
{
	UWorld* world = GetWorld();

	if (!isAlly)
	{
		world->GetGameState<ALostConnectionGameState>()->verteilenLootPoints(this);
	}

	Destroy();

	if (!isAlly)
	{
		world->GetAuthGameMode<ALostConnectionGameMode>()->getSpawnManager().notify(world);
	}
}

void ABaseBot::updateCharacterVisual()
{
	if (swarm.IsValid())
	{
		healthBarMaterial->SetScalarParameterValue("ThresholdPercent", swarm->getThreshold());
	}
}

ABaseBot::ABaseBot()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> healthBarBaseMaterialFinder(TEXT("Material'/Game/Assets/FX/M_HealthBar.M_HealthBar'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> textMaterialFinder(TEXT("Material'/Game/Assets/FX/M_NumericLife.M_NumericLife'"));
	static ConstructorHelpers::FObjectFinder<UFont> textFontFinder(TEXT("Font'/Engine/EditorResources/SmallFont.SmallFont'"));

	isAlly = false;

	healthBar = CreateDefaultSubobject<UMaterialBillboardComponent>("HealthBar");
	healthBarTextRender = CreateDefaultSubobject<UTextRenderComponent>("healthBarTextRender");

	healthBar->SetupAttachment(GetMesh());

	healthBarTextRender->SetupAttachment(healthBar);

	healthBar->AddRelativeLocation(FVector(0.0f, 0.0f, 187.0f));

	healthBarTextRender->SetTextMaterial(textMaterialFinder.Object);

	healthBarTextRender->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	healthBarTextRender->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	healthBarTextRender->SetTextRenderColor(FColor::White);
	healthBarTextRender->SetFont(textFontFinder.Object);
	healthBarTextRender->SetWorldSize(15.0f);

	baseHealthBarMaterial = healthBarBaseMaterialFinder.Object;

	healthBar->SetVisibility(false);

	healthBarTextRender->SetVisibility(false);
}

void ABaseBot::updateShield()
{
	if (IsValid(healthBarMaterial))
	{
		healthBarMaterial->SetVectorParameterValue("ShieldColor", energyShield->getEnergyShieldColor());
	}
}

int32 ABaseBot::getLootPoints() const
{
	return lootPointsReward;
}
