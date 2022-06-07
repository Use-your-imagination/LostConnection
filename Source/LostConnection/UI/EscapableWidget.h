// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "EscapableWidget.generated.h"

#pragma warning(disable: 4458)

UCLASS()
class LOSTCONNECTION_API UEscapableWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = UI, BlueprintReadOnly)
	int32 zOrder;

	UPROPERTY(Category = UI, EditDefaultsOnly, BlueprintReadOnly)
	bool isPreviousHitTestable;

	UPROPERTY(Category = UI, EditDefaultsOnly, BlueprintReadOnly)
	bool isPreviousVisible;

public:
	virtual void init(TObjectPtr<class ALostConnectionPlayerState> playerState);

	void updateAsTop();

	void updateAsPrevious(bool isVisible, bool isHitTestable);

	UFUNCTION(Category = Network, BlueprintNativeEvent)
	void onNetUpdate();

	void setZOrder(int32 zOrder);

	int32 getZOrder() const;

	bool getIsPreviousHitTestable() const;

	bool getIsPreviousVisible() const;

	virtual ~UEscapableWidget() = default;
};
