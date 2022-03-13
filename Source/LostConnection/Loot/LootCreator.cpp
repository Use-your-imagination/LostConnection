// Copyright (c) 2022 Use-your-imagination

#include "LootCreator.h"

#include "Kismet/KismetMathLibrary.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "Utility/Utility.h"

void LootCreator::createRandomWeapon(int32 lootPoints, UInventory* playerInventory, const TArray<UBaseWeaponsLootFunction*>& lootFunctions)
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
			weaponRarityRanges.Emplace(1.0f, chance, rarity);
		}
	}

	float chance = FMath::FRandRange(1.0f, weaponRarityRanges.Last().Get<1>());
	TTuple<float, float, EWeaponRarity>* result = weaponRarityRanges.FindByPredicate([&chance](const TTuple<float, float, EWeaponRarity>& range)
		{
			return UKismetMathLibrary::InRange_FloatFloat(chance, range.Get<0>(), range.Get<1>());
		}
	);

	if (result)
	{
		UBaseWeapon* weapon = NewObject<UBaseWeapon>(playerInventory->getPlayerState(), weaponClass);

		weapon->setWeaponRarity(result->Get<2>());

		playerInventory->addUnequippedWeapon(weapon);
	}
}
