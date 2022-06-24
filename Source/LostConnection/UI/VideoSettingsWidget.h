// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"

#include "VideoSettingsWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FApplySettingsDelegate, UGameUserSettings*, userSettings, int32, value);

UCLASS()
class LOSTCONNECTION_API UVideoSettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Widgets, BlueprintReadOnly, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> videoSettingName;

	UPROPERTY(Category = Widgets, BlueprintReadOnly, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UComboBoxString> videoSettingValue;

	UPROPERTY(Category = WidgetsContent, EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	FText settingName;

	UPROPERTY(Category = WidgetsContent, EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	TArray<FText> options;

	UPROPERTY(Category = WidgetsContent, EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	FText settingNameToolTip;

	UPROPERTY(Category = WidgetsContent, EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	FText optionsToolTip;

private:
	void NativePreConstruct() override;

public:
	TObjectPtr<UComboBoxString> getVideoSettingValue() const;
};

USTRUCT(BlueprintType)
struct LOSTCONNECTION_API FVideoSettings
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TMap<TObjectPtr<UVideoSettingsWidget>, FApplySettingsDelegate> settingsAppliers;

	FVideoSettings() = default;

	~FVideoSettings() = default;
};
