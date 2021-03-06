// Copyright (c) 2021 Use Your Imagination

#include "Utility.h"

#include "Algo/Count.h"
#include "Kismet/KismetMathLibrary.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Statuses/BaseStatus.h"
#include "Characters/BaseDrone.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"
#include "Weapons/BaseWeapon.h"
#include "Inventory/Inventory.h"

DEFINE_LOG_CATEGORY(LogLostConnection);

int32 Utility::countStatuses(const IStatusReceiver* target, const TSubclassOf<UBaseStatus>& statusClass)
{
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	return Algo::CountIf(statuses, [&statusClass](const UBaseStatus* status) { return UKismetMathLibrary::ClassIsChildOf(statusClass, status->StaticClass()); });
}

FText Utility::getTextFromFloat(float value)
{
	static constexpr int32 digits = 3;

	FString stringValue = FString::Printf(TEXT("%.0f"), value);
	FString thousandSymbol = FText::FromStringTable("/Game/Text/Common.Common", "ThousandSymbol").ToString();

	if (!(stringValue.Len() >= digits * 2 || stringValue.Len() <= digits))
	{
		stringValue.InsertAt(stringValue.Len() % digits, '.');

		while (true)
		{
			stringValue.MidInline(0, stringValue.Len() - 1);

			TCHAR last = stringValue[stringValue.Len() - 1];

			if (last == TCHAR('0') || last == TCHAR('.'))
			{
				continue;
			}

			if (stringValue.Len() <= digits + 1)
			{
				break;
			}
		}

		stringValue += thousandSymbol;
	}
	else if (stringValue.Len() >= digits * 2)
	{
		stringValue.MidInline(0, digits);

		stringValue += thousandSymbol;
	}

	return FText::FromString(MoveTemp(stringValue));
}

TSubclassOf<ABaseDrone> Utility::findDroneClass(const TArray<const UBaseDroneDataAsset*>& drones, const TSubclassOf<ABaseDrone>& drone)
{
	TSubclassOf<ABaseDrone> result;

	for (const auto& i : drones)
	{
		const auto& tem = i->getDrone();

		if (UKismetMathLibrary::ClassIsChildOf(tem, drone))
		{
			result = tem;

			break;
		}
	}

	return result;
}

void Utility::executeOnlyOnServerFromMulticast(TObjectPtr<AActor> actor, const TFunction<void()>& function)
{
	if (actor && actor->HasAuthority())
	{
		function();
	}
}

bool Utility::isYourPawn(APawn* pawn)
{
	return IsValid(pawn) && (pawn->GetController() == GEngine->GetFirstLocalPlayerController(pawn->GetWorld()));
}

void Utility::resetDamageInflictor(IDamageInflictor* inflictor)
{
	inflictor->setBaseDamage(0.0f);

	inflictor->setAddedDamage(0.0f);

	inflictor->setAdditionalDamage(0.0f);

	const_cast<TArray<float>&>(inflictor->getIncreaseDamageCoefficients()).Empty();

	const_cast<TArray<float>&>(inflictor->getMoreDamageCoefficients()).Empty();
}

TObjectPtr<UBaseWeapon> Utility::createWeapon(TSubclassOf<UBaseWeapon> weaponClass, EWeaponRarity rarity, TObjectPtr<AInventory> inventory)
{
	TObjectPtr<UBaseWeapon> weapon = NewObject<UBaseWeapon>(inventory, weaponClass);

	weapon->setRarity(rarity);

	return weapon;
}
