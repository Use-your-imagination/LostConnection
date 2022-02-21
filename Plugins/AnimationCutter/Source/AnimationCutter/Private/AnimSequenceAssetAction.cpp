// Copyright (c) 2022 Arkadiy Zakharov

#include "AnimSequenceAssetAction.h"

#include "Animation/AnimSequence.h"
#include "ToolMenus.h"
#include "EditorStyleSet.h"
#include "EditorReimportHandler.h"
#include "Animation/AnimMontage.h"
#include "Factories/AnimCompositeFactory.h"
#include "Factories/AnimStreamableFactory.h"
#include "Factories/AnimMontageFactory.h"
#include "Factories/PoseAssetFactory.h"
#include "EditorFramework/AssetImportData.h"
#include "Animation/AnimComposite.h"
#include "Animation/AnimStreamable.h"
#include "Animation/PoseAsset.h"
#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"
#include "IAnimationModifiersModule.h"
#include "Algo/Transform.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

void FAnimSequenceAssetAction::FillCreateMenu(FMenuBuilder& MenuBuilder, const TArray<TWeakObjectPtr<UAnimSequence>> Sequences) const
{
	MenuBuilder.AddMenuEntry
	(
		LOCTEXT("AnimSequence_NewAnimComposite", "Create AnimComposite"),
		LOCTEXT("AnimSequence_NewAnimCompositeTooltip", "Creates an AnimComposite using the selected anim sequence."),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "ClassIcon.AnimComposite"),
		FUIAction(FExecuteAction::CreateSP(this, &FAnimSequenceAssetAction::ExecuteNewAnimComposite, Sequences), FCanExecuteAction())
	);

	MenuBuilder.AddMenuEntry
	(
		LOCTEXT("AnimSequence_NewAnimMontage", "Create AnimMontage"),
		LOCTEXT("AnimSequence_NewAnimMontageTooltip", "Creates an AnimMontage using the selected anim sequence."),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "ClassIcon.AnimMontage"),
		FUIAction(FExecuteAction::CreateSP(this, &FAnimSequenceAssetAction::ExecuteNewAnimMontage, Sequences), FCanExecuteAction())
	);

	MenuBuilder.AddMenuEntry
	(
		LOCTEXT("AnimSequence_NewPoseAsset", "Create PoseAsset"),
		LOCTEXT("AnimSequence_NewPoseAssetTooltip", "Creates an PoseAsset using the selected anim sequence."),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "ClassIcon.PoseAsset"),
		FUIAction(FExecuteAction::CreateSP(this, &FAnimSequenceAssetAction::ExecuteNewPoseAsset, Sequences), FCanExecuteAction())
	);
}

void FAnimSequenceAssetAction::ExecuteReimportWithNewSource(TArray<TWeakObjectPtr<UAnimSequence>> Objects)
{
	FAssetImportInfo EmptyImportInfo;
	TArray<UObject*> ReimportAssets;

	for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		UObject* Object = (*ObjIt).Get();
		if (Object)
		{
			ReimportAssets.Add(Object);
		}
	}

	bool bShowNotification = !FApp::IsUnattended();
	bool bReimportWithNewFile = true;
	int32 SourceFileIndex = INDEX_NONE;

	FReimportManager::Instance()->ValidateAllSourceFileAndReimport(ReimportAssets, bShowNotification, SourceFileIndex, bReimportWithNewFile);
}

void FAnimSequenceAssetAction::ExecuteNewAnimComposite(TArray<TWeakObjectPtr<UAnimSequence>> Objects) const
{
	static const FString DefaultSuffix = "_Composite";
	UAnimCompositeFactory* Factory = NewObject<UAnimCompositeFactory>();

	CreateAnimationAssets(Objects, UAnimComposite::StaticClass(), Factory, DefaultSuffix, FOnConfigureFactory::CreateSP(this, &FAnimSequenceAssetAction::ConfigureFactoryForAnimComposite));
}

void FAnimSequenceAssetAction::ExecuteNewAnimMontage(TArray<TWeakObjectPtr<UAnimSequence>> Objects) const
{
	static const FString DefaultSuffix = "_Montage";
	UAnimMontageFactory* Factory = NewObject<UAnimMontageFactory>();

	CreateAnimationAssets(Objects, UAnimMontage::StaticClass(), Factory, DefaultSuffix, FOnConfigureFactory::CreateSP(this, &FAnimSequenceAssetAction::ConfigureFactoryForAnimMontage));
}

void FAnimSequenceAssetAction::ExecuteNewAnimStreamable(TArray<TWeakObjectPtr<UAnimSequence>> Objects) const
{
	static const FString DefaultSuffix = "_Streamable";
	UAnimStreamableFactory* Factory = NewObject<UAnimStreamableFactory>();

	auto StreamableConfigure = [](UFactory* AssetFactory, UAnimSequence* SourceAnimation) -> bool
	{
		UAnimStreamableFactory* StreamableAnimFactory = CastChecked<UAnimStreamableFactory>(AssetFactory);

		StreamableAnimFactory->SourceAnimation = SourceAnimation;

		return true;
	};

	CreateAnimationAssets(Objects, UAnimStreamable::StaticClass(), Factory, DefaultSuffix, FOnConfigureFactory::CreateLambda(StreamableConfigure));
}

void FAnimSequenceAssetAction::ExecuteNewPoseAsset(TArray<TWeakObjectPtr<UAnimSequence>> Objects) const
{
	static const FString DefaultSuffix = "_PoseAsset";
	UPoseAssetFactory* Factory = NewObject<UPoseAssetFactory>();

	CreateAnimationAssets(Objects, UPoseAsset::StaticClass(), Factory, DefaultSuffix, FOnConfigureFactory::CreateSP(this, &FAnimSequenceAssetAction::ConfigureFactoryForPoseAsset));
}

void FAnimSequenceAssetAction::ExecuteAddNewAnimationModifier(TArray<TWeakObjectPtr<UAnimSequence>> Objects)
{
	TArray<UAnimSequence*> AnimSequences;

	Algo::TransformIf(Objects, AnimSequences,
		[](const TWeakObjectPtr<UAnimSequence>& WeakAnimSequence)
		{
			return WeakAnimSequence.Get() && WeakAnimSequence->IsA<UAnimSequence>();
		},
		[](const TWeakObjectPtr<UAnimSequence>& WeakAnimSequence)
		{
			return WeakAnimSequence.Get();
		});

	if (IAnimationModifiersModule* Module = FModuleManager::Get().LoadModulePtr<IAnimationModifiersModule>("AnimationModifiers"))
	{
		Module->ShowAddAnimationModifierWindow(AnimSequences);
	}
}

bool FAnimSequenceAssetAction::ConfigureFactoryForAnimComposite(UFactory* AssetFactory, UAnimSequence* SourceAnimation) const
{
	UAnimCompositeFactory* CompositeFactory = CastChecked<UAnimCompositeFactory>(AssetFactory);

	CompositeFactory->SourceAnimation = SourceAnimation;

	return true;
}

bool FAnimSequenceAssetAction::ConfigureFactoryForAnimMontage(UFactory* AssetFactory, UAnimSequence* SourceAnimation) const
{
	UAnimMontageFactory* MontageFactory = CastChecked<UAnimMontageFactory>(AssetFactory);

	MontageFactory->SourceAnimation = SourceAnimation;

	return true;
}

bool FAnimSequenceAssetAction::ConfigureFactoryForPoseAsset(UFactory* AssetFactory, UAnimSequence* SourceAnimation) const
{
	UPoseAssetFactory* CompositeFactory = CastChecked<UPoseAssetFactory>(AssetFactory);

	CompositeFactory->SourceAnimation = SourceAnimation;

	return CompositeFactory->ConfigureProperties();
}

void FAnimSequenceAssetAction::CreateAnimationAssets(const TArray<TWeakObjectPtr<UAnimSequence>>& AnimSequences, TSubclassOf<UAnimationAsset> AssetClass, UFactory* AssetFactory, const FString& InSuffix, FOnConfigureFactory OnConfigureFactory) const
{
	if (AnimSequences.Num() == 1)
	{
		auto AnimSequence = AnimSequences[0].Get();

		if (AnimSequence)
		{
			FString Name;
			FString PackageName;

			CreateUniqueAssetName(AnimSequence->GetOutermost()->GetName(), InSuffix, PackageName, Name);

			if (OnConfigureFactory.IsBound())
			{
				if (OnConfigureFactory.Execute(AssetFactory, AnimSequence))
				{
					FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

					ContentBrowserModule.Get().CreateNewAsset(Name, FPackageName::GetLongPackagePath(PackageName), AssetClass, AssetFactory);
				}
			}
		}
	}
	else
	{
		TArray<UObject*> ObjectsToSync;

		for (auto SeqIt = AnimSequences.CreateConstIterator(); SeqIt; ++SeqIt)
		{
			UAnimSequence* AnimSequence = (*SeqIt).Get();

			if (AnimSequence)
			{
				FString Name;
				FString PackageName;

				CreateUniqueAssetName(AnimSequence->GetOutermost()->GetName(), InSuffix, PackageName, Name);

				if (OnConfigureFactory.IsBound())
				{
					if (OnConfigureFactory.Execute(AssetFactory, AnimSequence))
					{
						FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
						UAnimationAsset* NewAsset = Cast<UAnimationAsset>(AssetToolsModule.Get().CreateAsset(Name, FPackageName::GetLongPackagePath(PackageName), AssetClass, AssetFactory));

						if (NewAsset)
						{
							NewAsset->MarkPackageDirty();
							ObjectsToSync.Add(NewAsset);
						}
					}
				}
			}
		}

		if (ObjectsToSync.Num() > 0)
		{
			FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

			ContentBrowserModule.Get().SyncBrowserToAssets(ObjectsToSync, true);
		}
	}
}

FText FAnimSequenceAssetAction::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_AnimSequence", "Animation Sequence");
}

UClass* FAnimSequenceAssetAction::GetSupportedClass() const
{
	return UAnimSequence::StaticClass();
}

void FAnimSequenceAssetAction::GetActions(const TArray<UObject*>& InObjects, FToolMenuSection& Section)
{
	auto Sequences = GetTypedWeakObjectPtrs<UAnimSequence>(InObjects);

	Section.AddSubMenu
	(
		"CreateAnimSubmenu",
		LOCTEXT("CreateAnimSubmenu", "Create"),
		LOCTEXT("CreateAnimSubmenu_ToolTip", "Create assets from this anim sequence"),
		FNewMenuDelegate::CreateSP(this, &FAnimSequenceAssetAction::FillCreateMenu, Sequences),
		false,
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Persona.AssetActions.CreateAnimAsset")
	);

	Section.AddMenuEntry
	(
		"AnimSequence_ReimportWithNewSource",
		LOCTEXT("AnimSequence_ReimportWithNewSource", "Reimport with New Source"),
		LOCTEXT("AnimSequence_ReimportWithNewSourceTooltip", "Reimport the selected sequence(s) from a new source file."),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Persona.AssetActions.ReimportAnim"),
		FUIAction(FExecuteAction::CreateSP(this, &FAnimSequenceAssetAction::ExecuteReimportWithNewSource, Sequences))
	);

	Section.AddMenuEntry
	(
		"AnimSequence_AddAnimationModifier",
		LOCTEXT("AnimSequence_AddAnimationModifier", "Add Animation Modifier(s)"),
		LOCTEXT("AnimSequence_AddAnimationModifierTooltip", "Apply new animation modifier(s)."),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "ClassIcon.AnimationModifier"),
		FUIAction(FExecuteAction::CreateSP(this, &FAnimSequenceAssetAction::ExecuteAddNewAnimationModifier, Sequences))
	);

	FAnimationAssetAction::GetActions(InObjects, Section);
}

bool FAnimSequenceAssetAction::CanFilter()
{
	return true;
}

bool FAnimSequenceAssetAction::IsImportedAsset() const
{
	return true;
}

void FAnimSequenceAssetAction::GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const
{
	for (auto& Asset : TypeAssets)
	{
		const auto AnimSequence = CastChecked<UAnimSequence>(Asset);

		AnimSequence->AssetImportData->ExtractFilenames(OutSourceFilePaths);
	}
}

#undef LOCTEXT_NAMESPACE
