// Copyright (c) 2022 Use-your-imagination

#include "LootCreator.h"

#include "Kismet/KismetMathLibrary.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "Utility/Utility.h"
#include "Characters/BaseDrone.h"

void LootCreator::createRandomWeapon(int32 lootPoints, AInventory* playerInventory, const TArray<UBaseWeaponsLootFunction*>& lootFunctions)
{
	const TSubclassOf<UBaseWeapon>& weaponClass = Utility::getRandomValueFromArray(ULostConnectionAssetManager::get().getLoot().getWeapons());
	TArray<TTuple<float, float, EWeaponRarity>> weaponRarityRanges;

	weaponRarityRanges.Reserve(lootFunctions.Num());

	for (UBaseWeaponsLootFunction* lootFunction : lootFunctions)
	{
		float chance = lootFunction->calculateLootChance(lootPoints);
		EWeaponRarity rarity = lootFunction->getWeaponRarity();

		if (weaponRarityRanges.Num())
		{
			float rangeEnd = weaponRarityRanges.Last().Get<1>();

			weaponRarityRanges.Emplace(rangeEnd, rangeEnd + chance, rarity);
		}
		else
		{
			weaponRarityRanges.Emplace(0.0f, chance, rarity);
		}
	}

	float chance = FMath::FRandRange(0.0f, 100.0f);
	TTuple<float, float, EWeaponRarity>* result = weaponRarityRanges.FindByPredicate([&chance](const TTuple<float, float, EWeaponRarity>& range)
		{
			const float& begin = range.Get<0>();
			const float& end = range.Get<1>();

			return begin != end && UKismetMathLibrary::InRange_FloatFloat(chance, begin, end);
		}
	);

	if (result)
	{
		UBaseWeapon* weapon = NewObject<UBaseWeapon>(playerInventory->getPlayerState(), weaponClass);

		weapon->setWeaponRarity(result->Get<2>());

		playerInventory->addUnequippedWeapon(weapon);

		if (ABaseDrone* drone = playerInventory->getPlayerState()->GetPawn<ABaseDrone>())
		{
			weapon->setOwner(drone);

			weapon->updateTimeBetweenShots();
		}
	}
}
