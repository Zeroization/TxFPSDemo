// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TXFPSDEMO_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurScoreText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CountDownText;

public:
	void UpdatePlayerScore(float NewScore);
	void UpdateCountDown(float NewCountDown);
};
