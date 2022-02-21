// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "Animation/AnimationAsset.h"

#include "AnimationAssetAction.h"

class UAnimSequence;
class UFactory;

DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnConfigureFactory, UFactory*, UAnimSequence*);

class FAnimSequenceAssetAction : public FAnimationAssetAction
{
private:
	void FillCreateMenu(FMenuBuilder& MenuBuilder, const TArray<TWeakObjectPtr<UAnimSequence>> Sequences) const;

	void ExecuteReimportWithNewSource(TArray<TWeakObjectPtr<UAnimSequence>> Objects);

	void ExecuteNewAnimComposite(TArray<TWeakObjectPtr<UAnimSequence>> Objects) const;

	void ExecuteNewAnimMontage(TArray<TWeakObjectPtr<UAnimSequence>> Objects) const;

	void ExecuteNewAnimStreamable(TArray<TWeakObjectPtr<UAnimSequence>> Objects) const;

	void ExecuteNewPoseAsset(TArray<TWeakObjectPtr<UAnimSequence>> Objects) const;

	void ExecuteAddNewAnimationModifier(TArray<TWeakObjectPtr<UAnimSequence>> Objects);

	bool ConfigureFactoryForAnimComposite(UFactory* AssetFactory, UAnimSequence* SourceAnimation) const;

	bool ConfigureFactoryForAnimMontage(UFactory* AssetFactory, UAnimSequence* SourceAnimation) const;

	bool ConfigureFactoryForPoseAsset(UFactory* AssetFactory, UAnimSequence* SourceAnimation) const;

	void CreateAnimationAssets(const TArray<TWeakObjectPtr<UAnimSequence>>& AnimSequences, TSubclassOf<UAnimationAsset> AssetClass, UFactory* AssetFactory, const FString& InSuffix, FOnConfigureFactory OnConfigureFactory) const;

public:
	FAnimSequenceAssetAction() = default;

	virtual FText GetName() const final override;

	virtual UClass* GetSupportedClass() const final override;

	virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;

	virtual bool CanFilter() final override;

	virtual bool IsImportedAsset() const final override;

	virtual void GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const override final;

	virtual ~FAnimSequenceAssetAction() = default;
};
