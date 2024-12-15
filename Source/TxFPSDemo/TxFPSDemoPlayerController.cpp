// Copyright Epic Games, Inc. All Rights Reserved.


#include "TxFPSDemoPlayerController.h"
#include "HUDWidget.h"
#include "EnhancedInputSubsystems.h"
#include "GameOverWidget.h"
#include "Engine/LocalPlayer.h"

void ATxFPSDemoPlayerController::UpdateCurrentScore(float NewScore)
{
	if (HUDWidget != nullptr)
	{
		HUDWidget->UpdatePlayerScore(NewScore);
	}
}

void ATxFPSDemoPlayerController::UpdateCountdown(float NewCountdown)
{
	if (HUDWidget != nullptr)
	{
		HUDWidget->UpdateCountDown(NewCountdown);
	}
}

void ATxFPSDemoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	// 初始化HUD
	if (BP_HUDWidget != nullptr)
	{
		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		HUDWidget->AddToViewport();
	}
}

void ATxFPSDemoPlayerController::ShowGameOverWidget(const TArray<TPair<FString, float>>& PlayerScoreList)
{
	if (BP_GameOverWidget != nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;

		GameOverWidget = CreateWidget<UGameOverWidget>(this, BP_GameOverWidget);
		GameOverWidget->UpdatePlayerListBox(PlayerScoreList);
		GameOverWidget->AddToViewport();
	}
}

void ATxFPSDemoPlayerController::HideGameOverWidget()
{
	if (GameOverWidget != nullptr)
	{
		GameOverWidget->RemoveFromParent();
		GameOverWidget->Destruct();

		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
		SetPause(false);
	}
}
