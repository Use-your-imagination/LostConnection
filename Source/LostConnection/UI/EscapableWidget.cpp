// Copyright (c) 2022 Use-your-imagination

#include "EscapableWidget.h"

#include "Engine/LostConnectionPlayerState.h"

void UEscapableWidget::init(ALostConnectionPlayerState* playerState)
{

}

void UEscapableWidget::updateAsTop()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UEscapableWidget::updateAsPrevious(bool isVisible, bool isHitTestable)
{
	SetVisibility(isVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	if (isHitTestable)
	{
		SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UEscapableWidget::onNetUpdate_Implementation()
{

}

void UEscapableWidget::setZOrder(int32 zOrder)
{
	this->zOrder = zOrder;
}

int32 UEscapableWidget::getZOrder() const
{
	return zOrder;
}

bool UEscapableWidget::getIsPreviousHitTestable() const
{
	return isPreviousHitTestable;
}

bool UEscapableWidget::getIsPreviousVisible() const
{
	return isPreviousVisible;
}
