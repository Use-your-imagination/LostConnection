// Copyright (c) 2022 Arkadiy Zakharov

#include "AnimationAssetAction.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Misc/MessageDialog.h"
#include "EditorStyleSet.h"
#include "ThumbnailRendering/SceneThumbnailInfo.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "PersonaModule.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "SSkeletonWidget.h"
#include "IAnimationEditorModule.h"
#include "Preferences/PersonaOptions.h"
#include "ToolMenus.h"
#include "Framework/Application/SlateApplication.h"
#include "Algo/Transform.h"
#include "IPersonaToolkit.h"
#if WITH_EDITOR
#include "Subsystems/AssetEditorSubsystem.h"
#include "Editor.h"
#endif

#define LOCTEXT_NAMESPACE "AssetTypeActions"

void FAnimationAssetAction::FillRetargetMenu(FMenuBuilder& MenuBuilder, const TArray<UObject*> InObjects)
{
	bool bAllSkeletonsNull = true;

	for (auto Iter = InObjects.CreateConstIterator(); Iter; ++Iter)
	{
		if (UAnimationAsset* AnimAsset = Cast<UAnimationAsset>(*Iter))
		{
			if (AnimAsset->GetSkeleton())
			{
				bAllSkeletonsNull = false;
				break;
			}
		}
	}

	if (bAllSkeletonsNull)
	{
		MenuBuilder.AddMenuEntry(
			LOCTEXT("AnimAsset_RetargetSkeletonInPlace", "Retarget skeleton on existing Anim Assets"),
			LOCTEXT("AnimAsset_RetargetSkeletonInPlaceTooltip", "Retargets the selected Anim Assets to a new skeleton (and optionally all referenced animations too)"),
			FSlateIcon(FEditorStyle::GetStyleSetName(), "Persona.AssetActions.RetargetSkeleton"),
			FUIAction(
				FExecuteAction::CreateSP(this, &FAnimationAssetAction::RetargetAssets, InObjects, false, false, TSharedPtr<IToolkitHost>()),
				FCanExecuteAction()
			)
		);
	}

	MenuBuilder.AddMenuEntry(
		LOCTEXT("AnimAsset_DuplicateAndRetargetSkeleton", "Duplicate Anim Assets and Retarget"),
		LOCTEXT("AnimAsset_DuplicateAndRetargetSkeletonTooltip", "Duplicates and then retargets the selected Anim Assets to a new skeleton (and optionally all referenced animations too)"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Persona.AssetActions.DuplicateAndRetargetSkeleton"),
		FUIAction(
			FExecuteAction::CreateSP(this, &FAnimationAssetAction::RetargetAssets, InObjects, true, false, TSharedPtr<IToolkitHost>()),
			FCanExecuteAction()
		)
	);
}

void FAnimationAssetAction::ExecuteFindSkeleton(TArray<TWeakObjectPtr<UAnimationAsset>> Objects)
{
	TArray<UObject*> ObjectsToSync;
	for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Object = (*ObjIt).Get();
		if (Object)
		{
			USkeleton* Skeleton = Object->GetSkeleton();
			if (Skeleton)
			{
				ObjectsToSync.AddUnique(Skeleton);
			}
		}
	}

	if (ObjectsToSync.Num() > 0)
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

		ContentBrowserModule.Get().SyncBrowserToAssets(ObjectsToSync, true);
	}
}

void FAnimationAssetAction::ExecuteOpenInNewWindow(TArray<TWeakObjectPtr<UAnimationAsset>> Objects)
{
	TArray<UObject*> ObjectsToSync;
	Algo::Transform(Objects, ObjectsToSync, [](TWeakObjectPtr<UAnimationAsset> Obj) { return Obj.Get(); });

	OpenAnimAssetEditor(ObjectsToSync, true, nullptr);
}

void FAnimationAssetAction::OpenAnimAssetEditor(const TArray<UObject*>& InObjects, bool bForceNewEditor, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	bForceNewEditor |= FSlateApplication::Get().GetModifierKeys().IsShiftDown();

	TArray<UAnimationAsset*> AnimAssets;
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UAnimationAsset* AnimAsset = Cast<UAnimationAsset>(*ObjIt))
		{
			AnimAssets.Add(AnimAsset);
		}
	}

	for (UAnimationAsset* AnimAsset : AnimAssets)
	{
		USkeleton* AnimSkeleton = AnimAsset->GetSkeleton();
		if (!AnimSkeleton)
		{
			FText ShouldRetargetMessage = LOCTEXT("ShouldRetargetAnimAsset_Message", "Could not find the skeleton for Anim '{AnimName}' Would you like to choose a new one?");

			FFormatNamedArguments Arguments;
			Arguments.Add(TEXT("AnimName"), FText::FromString(AnimAsset->GetName()));

			if (FMessageDialog::Open(EAppMsgType::YesNo, FText::Format(ShouldRetargetMessage, Arguments)) == EAppReturnType::Yes)
			{
				bool bDuplicateAssets = false;
				TArray<UObject*> AssetsToRetarget;
				AssetsToRetarget.Add(AnimAsset);
				RetargetAssets(AssetsToRetarget, bDuplicateAssets, true, EditWithinLevelEditor);
			}
		}
		else
		{
			const bool bBringToFrontIfOpen = true;
#if WITH_EDITOR
			if (IAssetEditorInstance* EditorInstance = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(AnimAsset, bBringToFrontIfOpen))
			{
				EditorInstance->FocusWindow();
			}
			else
#endif
			{
				bool bSingleAsset = AnimAssets.Num() == 1;
				bool bFoundEditor = false;
				if (bSingleAsset && !bForceNewEditor)
				{
					TArray<UObject*> AllEditedAssets;
#if WITH_EDITOR
					AllEditedAssets = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->GetAllEditedAssets();
#endif
					UAnimationAsset* CompatibleEditedAsset = nullptr;
					for (UObject* EditedAsset : AllEditedAssets)
					{
						UAnimationAsset* EditedAnimAsset = Cast<UAnimationAsset>(EditedAsset);
						if (EditedAnimAsset && EditedAnimAsset->GetSkeleton() == AnimAsset->GetSkeleton())
						{
							CompatibleEditedAsset = EditedAnimAsset;
							break;
						}
					}

					if (CompatibleEditedAsset)
					{
						TArray<IAssetEditorInstance*> AssetEditors;
#if WITH_EDITOR
						AssetEditors = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorsForAsset(CompatibleEditedAsset);
#endif
						for (IAssetEditorInstance* ExistingEditor : AssetEditors)
						{
							if (ExistingEditor->GetEditorName() == FName("AnimationEditor"))
							{
								IAnimationEditor* AnimEditor = static_cast<IAnimationEditor*>(ExistingEditor);
								if (AnimEditor->GetPersonaToolkit()->GetSkeleton() == AnimAsset->GetSkeleton())
								{
									AnimEditor->SetAnimationAsset(AnimAsset);
									AnimEditor->FocusWindow();
									bFoundEditor = true;
									break;
								}
							}
						}
					}
				}

				if (!bFoundEditor)
				{
					IAnimationEditorModule& AnimationEditorModule = FModuleManager::LoadModuleChecked<IAnimationEditorModule>("AnimationEditor");
					AnimationEditorModule.CreateAnimationEditor(Mode, EditWithinLevelEditor, AnimAsset);
				}
			}
		}
	}
}

void FAnimationAssetAction::RetargetAssets(TArray<UObject*> InAnimAssets, bool bDuplicateAssets, bool bOpenEditor, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	bool bRemapReferencedAssets = false;
	USkeleton* NewSkeleton = NULL;
	USkeleton* OldSkeleton = NULL;
	if (InAnimAssets.Num() > 0)
	{
		UAnimationAsset* AnimAsset = CastChecked<UAnimationAsset>(InAnimAssets[0]);
		OldSkeleton = AnimAsset->GetSkeleton();
	}

	const FText Message = LOCTEXT("SelectSkeletonToRemap", "Select the skeleton to remap this asset to.");

	auto AnimAssets = GetTypedWeakObjectPtrs<UObject>(InAnimAssets);

	if (bOpenEditor)
	{
		//SAnimationRemapSkeleton::ShowWindow(OldSkeleton, Message, bDuplicateAssets, FOnRetargetAnimation::CreateSP(this, &FAnimationAssetAction::RetargetNonSkeletonAnimationHandler, AnimAssets, TWeakPtr<class IToolkitHost>(EditWithinLevelEditor)));
	}
	else
	{
		//SAnimationRemapSkeleton::ShowWindow(OldSkeleton, Message, bDuplicateAssets, FOnRetargetAnimation::CreateSP(this, &FAnimationAssetAction::RetargetAnimationHandler, AnimAssets));
	}
}

void FAnimationAssetAction::RetargetAnimationHandler(USkeleton* OldSkeleton, USkeleton* NewSkeleton, bool bRemapReferencedAssets, bool bAllowRemapToExisting, bool bConvertSpaces, const EditorAnimUtils::FNameDuplicationRule* NameRule, TArray<TWeakObjectPtr<UObject>> InAnimAssets)
{
	if (!OldSkeleton || OldSkeleton->GetPreviewMesh(false))
	{
		EditorAnimUtils::RetargetAnimations(OldSkeleton, NewSkeleton, InAnimAssets, bRemapReferencedAssets, NameRule, bConvertSpaces);
	}
	else
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("OldSkeletonName"), FText::FromString(GetNameSafe(OldSkeleton)));
		Args.Add(TEXT("NewSkeletonName"), FText::FromString(GetNameSafe(NewSkeleton)));
		FNotificationInfo Info(FText::Format(LOCTEXT("Retarget Failed", "Old Skeleton {OldSkeletonName} and New Skeleton {NewSkeletonName} need to have Preview Mesh set up to convert animation"), Args));
		Info.ExpireDuration = 5.0f;
		Info.bUseLargeFont = false;
		TSharedPtr<SNotificationItem> Notification = FSlateNotificationManager::Get().AddNotification(Info);
		if (Notification.IsValid())
		{
			Notification->SetCompletionState(SNotificationItem::CS_Fail);
		}
	}
}

void FAnimationAssetAction::RetargetNonSkeletonAnimationHandler(USkeleton* OldSkeleton, USkeleton* NewSkeleton, bool bRemapReferencedAssets, bool bAllowRemapToExisting, bool bConvertSpaces, const EditorAnimUtils::FNameDuplicationRule* NameRule, TArray<TWeakObjectPtr<UObject>> InAnimAssets, TWeakPtr<IToolkitHost> EditWithinLevelEditor)
{
	RetargetAnimationHandler(OldSkeleton, NewSkeleton, bRemapReferencedAssets, bAllowRemapToExisting, bConvertSpaces, NameRule, InAnimAssets);

#if WITH_EDITOR
	if (NewSkeleton)
	{
		for (auto Asset : InAnimAssets)
		{
			if (Asset.IsValid())
			{
				if (EditWithinLevelEditor.IsValid())
				{

					GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Asset.Get(), EToolkitMode::WorldCentric, EditWithinLevelEditor.Pin());
				}
				else
				{
					GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Asset.Get());
				}
			}
		}
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("FailedToLoadSkeletonlessAnimAsset", "The Anim Asset could not be loaded because it's skeleton is missing."));
	}
#endif

}

FText FAnimationAssetAction::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_AnimationAsset", "AnimationAsset");
}

FColor FAnimationAssetAction::GetTypeColor() const
{
	return FColor(80, 123, 72);
}

UClass* FAnimationAssetAction::GetSupportedClass() const
{
	return UAnimationAsset::StaticClass();
}

bool FAnimationAssetAction::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}

void FAnimationAssetAction::GetActions(const TArray<UObject*>& InObjects, FToolMenuSection& Section)
{
	auto AnimAssets = GetTypedWeakObjectPtrs<UAnimationAsset>(InObjects);

	Section.AddMenuEntry(
		"AnimSequenceBase_OpenInNewWindow",
		LOCTEXT("AnimSequenceBase_OpenInNewWindow", "Open In New Window"),
		LOCTEXT("AnimSequenceBase_OpenInNewWindowTooltip", "Will always open asset in a new window, and not re-use existing window. (Shift+Double-Click)"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "ContentBrowser.AssetActions.OpenInExternalEditor"),
		FUIAction(
			FExecuteAction::CreateSP(this, &FAnimationAssetAction::ExecuteOpenInNewWindow, AnimAssets),
			FCanExecuteAction()
		)
	);

	Section.AddMenuEntry(
		"AnimSequenceBase_FindSkeleton",
		LOCTEXT("AnimSequenceBase_FindSkeleton", "Find Skeleton"),
		LOCTEXT("AnimSequenceBase_FindSkeletonTooltip", "Finds the skeleton for the selected assets in the content browser."),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Persona.AssetActions.FindSkeleton"),
		FUIAction(
			FExecuteAction::CreateSP(this, &FAnimationAssetAction::ExecuteFindSkeleton, AnimAssets),
			FCanExecuteAction()
		)
	);

	Section.AddSubMenu(
		"RetargetAnimSubmenu",
		LOCTEXT("RetargetAnimSubmenu", "Retarget Anim Assets"),
		LOCTEXT("RetargetAnimSubmenu_ToolTip", "Opens the retarget anim assets menu"),
		FNewMenuDelegate::CreateSP(this, &FAnimationAssetAction::FillRetargetMenu, InObjects),
		false,
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Persona.AssetActions.RetargetSkeleton")
	);
}

void FAnimationAssetAction::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	OpenAnimAssetEditor(InObjects, false, EditWithinLevelEditor);
}

bool FAnimationAssetAction::CanFilter()
{
	return false;
}

uint32 FAnimationAssetAction::GetCategories()
{
	return EAssetTypeCategories::Animation;
}

UThumbnailInfo* FAnimationAssetAction::GetThumbnailInfo(UObject* Asset) const
{
	UAnimationAsset* Anim = CastChecked<UAnimationAsset>(Asset);
	UThumbnailInfo* ThumbnailInfo = Anim->ThumbnailInfo;
	if (ThumbnailInfo == NULL)
	{
		ThumbnailInfo = NewObject<USceneThumbnailInfo>(Anim, NAME_None, RF_Transactional);
		Anim->ThumbnailInfo = ThumbnailInfo;
	}

	return ThumbnailInfo;
}

#undef LOCTEXT_NAMESPACE
