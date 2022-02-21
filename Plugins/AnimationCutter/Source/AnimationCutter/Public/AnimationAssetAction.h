// Copyright (c) 2022 Arkadiy Zakharov

#pragma once

#include "CoreMinimal.h"

#include "Toolkits/IToolkitHost.h"
#include "AssetTypeActions_Base.h"
#include "Animation/AnimationAsset.h"
#include "EditorAnimUtils.h"

class FAnimationAssetAction : public FAssetTypeActions_Base
{
private:
	void FillRetargetMenu(FMenuBuilder& MenuBuilder, const TArray<UObject*> InObjects);

	void ExecuteFindSkeleton(TArray<TWeakObjectPtr<UAnimationAsset>> Objects);

	void ExecuteOpenInNewWindow(TArray<TWeakObjectPtr<UAnimationAsset>> Objects);

	void OpenAnimAssetEditor(const TArray<UObject*>& InObjects, bool bForceNewEditor, TSharedPtr<IToolkitHost> EditWithinLevelEditor);

	void RetargetAssets(TArray<UObject*> InAnimBlueprints, bool bDuplicateAssets, bool bOpenEditor, TSharedPtr<class IToolkitHost> EditWithinLevelEditor);

	void RetargetAnimationHandler(USkeleton* OldSkeleton, USkeleton* NewSkeleton, bool bRemapReferencedAssets, bool bAllowRemapToExisting, bool bConvertSpaces, const EditorAnimUtils::FNameDuplicationRule* NameRule, TArray<TWeakObjectPtr<UObject>> InAnimAssets);

	void RetargetNonSkeletonAnimationHandler(USkeleton* OldSkeleton, USkeleton* NewSkeleton, bool bRemapReferencedAssets, bool bAllowRemapToExisting, bool bConvertSpaces, const EditorAnimUtils::FNameDuplicationRule* NameRule, TArray<TWeakObjectPtr<UObject>> InAnimAssets, TWeakPtr<class IToolkitHost> EditWithinLevelEditor);

public:
	FAnimationAssetAction() = default;

	virtual FText GetName() const override;

	virtual FColor GetTypeColor() const override;

	virtual UClass* GetSupportedClass() const override;

	virtual bool HasActions(const TArray<UObject*>& InObjects) const override;

	virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;

	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

	virtual bool CanFilter() override;

	virtual uint32 GetCategories() override;

	virtual class UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override;

	virtual ~FAnimationAssetAction() = default;
};
