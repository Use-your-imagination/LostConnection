// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "Utility/Enums.h"

#include "BaseActDataAsset.generated.h"

UCLASS(Abstract, BlueprintType)
class LOSTCONNECTION_API UBaseActDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Levels, EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> startingRooms;

	UPROPERTY(Category = Levels, EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> rooms;

	UPROPERTY(Category = Levels, EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> secretRooms;

	UPROPERTY(Category = Levels, EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> warehouses;

	UPROPERTY(Category = Levels, EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> bossRooms;

	UPROPERTY(Category = AI, EditDefaultsOnly, BlueprintReadOnly, Meta = (MustImplement = MeleeBot))
	TArray<TSubclassOf<class ABaseBot>> meleeBots;

	UPROPERTY(Category = AI, EditDefaultsOnly, BlueprintReadOnly, Meta = (MustImplement = RangedBot))
	TArray<TSubclassOf<class ABaseBot>> rangedBots;

	UPROPERTY(Category = AI, EditDefaultsOnly, BlueprintReadOnly, Meta = (MustImplement = SniperBot))
	TArray<TSubclassOf<class ABaseBot>> sniperBots;

	UPROPERTY(Category = AI, EditDefaultsOnly, BlueprintReadOnly, Meta = (MustImplement = CasterBot))
	TArray<TSubclassOf<class ABaseBot>> casterBots;

	UPROPERTY(Category = AI, EditDefaultsOnly, BlueprintReadOnly, Meta = (MustImplement = SupportBot))
	TArray<TSubclassOf<class ABaseBot>> supportBots;

	UPROPERTY(Category = AI, EditDefaultsOnly, BlueprintReadOnly, Meta = (MustImplement = AssassinBot))
	TArray<TSubclassOf<class ABaseBot>> assassinBots;

protected:
	static FPrimaryAssetType getPrimaryAssetType();

public:
	UBaseActDataAsset() = default;

	const TArray<TSoftObjectPtr<UWorld>>& getRooms() const;

	const TArray<TSubclassOf<class ABaseBot>>& operator [] (EBotType type) const;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UBaseActDataAsset() = default;
};
