// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

#include "Components/TextBlock.h"


void UHUDWidget::UpdatePlayerScore(float NewScore)
{
	if (CurScoreText != nullptr)
	{
		CurScoreText->SetText(FText::AsNumber(NewScore));
	}
}

void UHUDWidget::UpdateCountDown(float NewCountDown)
{
	if (CountDownText != nullptr)
	{
		CountDownText->SetText(FText::AsNumber(NewCountDown));
	}
}
