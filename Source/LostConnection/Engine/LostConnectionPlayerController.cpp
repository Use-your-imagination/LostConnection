// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionPlayerController.h"

#include "Kismet/GameplayStatics.h"

#include "Constants/Constants.h"
#include "LostConnectionPlayerState.h"
#include "Characters/BaseDrone.h"
#include "Characters/BaseBot.h"
#include "Weapons/SubmachineGuns/Hipter.h"
#include "Weapons/Pistols/Gauss.h"

void ALostConnectionPlayerController::BeginPlay()
{
	ULostConnectionAssetManager& manager = ULostConnectionAssetManager::get();
	ALostConnectionPlayerState* playerState = GetPlayerState<ALostConnectionPlayerState>();
	APawn* pawn = GetPawn();

	if (this == UGameplayStatics::GetPlayerController(this, 0))
	{
		if (ABaseDrone* drone = Cast<ABaseDrone>(pawn))
		{
			GEngine->AddOnScreenDebugMessage(-1, 120.0f, FColor::Red, FString::Printf(L"player state: %d", StaticCast<bool>(PlayerState)));

			ULostConnectionUI* defaultUI = NewObject<ULostConnectionUI>(playerState, manager.getUI().getDefaultUI());

			playerState->init();

			defaultUI->init(drone);

			playerState->setCurrentUI(defaultUI);
		}
	}

	if (HasAuthority())
	{
		TArray<FAmmoData>& spareAmmo = playerState->getSpareAmmoArray();

		if (ABaseCharacter* character = Cast<ABaseCharacter>(pawn))
		{
			if (!spareAmmo.Num())
			{
				spareAmmo =
				{
					FAmmoData(ammoTypes::small, character->getDefaultSmallAmmoCount()),
					FAmmoData(ammoTypes::large, character->getDefaultLargeAmmoCount()),
					FAmmoData(ammoTypes::energy, character->getDefaultEnergyAmmoCount()),
					FAmmoData(ammoTypes::defaultType, 9999)
				};
			}
		}

		if (ABaseDrone* drone = Cast<ABaseDrone>(pawn))
		{
			drone->setPrimaryWeapon(manager.getWeaponClass(UHipter::StaticClass()));

			drone->setDefaultWeapon(manager.getWeaponClass(UGauss::StaticClass()));
		}

		if (ABaseBot* bot = Cast<ABaseBot>(pawn))
		{
			
		}
	}
}

void ALostConnectionPlayerController::GetSeamlessTravelActorList(bool bToEntry, TArray<AActor*>& ActorList)
{
	ActorList.Add(GetPawn());

	Super::GetSeamlessTravelActorList(bToEntry, ActorList);
}

ALostConnectionPlayerController::ALostConnectionPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
}
