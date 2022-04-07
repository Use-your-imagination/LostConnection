// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Templates/SubclassOf.h"
#include "Animation/AnimationAsset.h"

#include "AnimationAssetAction.h"

class UAnimSequence;
class UFactory;

DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnConfigureFactory, class UFactory*, class UAnimSequence*);

class FAnimSequenceAssetAction : public FAnimationAssetAction
{
private:
	void ExecuteReimportWithNewSource(TArray<TWeakObjectPtr<UAnimSequence>> Objects);

	void ExecuteNewAnimComposite(TArray<TWeakObjectPtr<UAnimSequence>> Objects) const;

	void ExecuteNewAnimMontage(TArray<TWeakObjectPtr<UAnimSequence>> Objects) const;

	void ExecuteNewAnimStreamable(TArray<TWeakObjectPtr<UAnimSequence>> Objects) const;

	void ExecuteNewPoseAsset(TArray<TWeakObjectPtr<UAnimSequence>> Objects) const;

	bool ConfigureFactoryForAnimComposite(UFactory* AssetFactory, UAnimSequence* SourceAnimation) const;

	bool ConfigureFactoryForAnimMontage(UFactory* AssetFactory, UAnimSequence* SourceAnimation) const;

	bool ConfigureFactoryForPoseAsset(UFactory* AssetFactory, UAnimSequence* SourceAnimation) const;

	void CreateAnimationAssets(const TArray<TWeakObjectPtr<UAnimSequence>>& AnimSequences, TSubclassOf<UAnimationAsset> AssetClass, UFactory* AssetFactory, const FString& InSuffix, FOnConfigureFactory OnConfigureFactory) const;

	void FillCreateMenu(FMenuBuilder& MenuBuilder, const TArray<TWeakObjectPtr<UAnimSequence>> Sequences) const;

public:
	virtual FText GetName() const override;

	virtual UClass* GetSupportedClass() const override;

	virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;

	virtual bool CanFilter() override;

	virtual bool IsImportedAsset() const override;

	virtual void GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const override;
};
