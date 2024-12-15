// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

#include "TxFPSDemoPlayerController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"


void UGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 绑定按钮回调
	if (RestartBtn != nullptr)
	{
		RestartBtn->OnClicked.AddDynamic(this, &UGameOverWidget::OnRestartClicked);
	}

	if (ExitBtn != nullptr)
	{
		ExitBtn->OnClicked.AddDynamic(this, &UGameOverWidget::OnExitClicked);
	}
}

void UGameOverWidget::UpdatePlayerListBox(const TArray<TPair<FString, float>>& PlayerScoreList)
{
	float TotalScore = 0.f;

	if (PlayerListBox != nullptr)
	{
		PlayerListBox->ClearChildren();

		for (const auto& PlayerInfo : PlayerScoreList)
		{
			UTextBlock* TextBlock = NewObject<UTextBlock>(PlayerListBox);
			if (TextBlock != nullptr)
			{
				TotalScore += PlayerInfo.Value;
				FString Data = FString::Printf(TEXT("%s\t\t\t%f"), *PlayerInfo.Key, PlayerInfo.Value);
				TextBlock->SetText(FText::FromString(Data));

				PlayerListBox->AddChildToVerticalBox(TextBlock);
			}
		}
	}

	if (TotalScoreText != nullptr)
	{
		TotalScoreText->SetText(FText::AsNumber(TotalScore));
	}
}

void UGameOverWidget::OnRestartClicked()
{
	ATxFPSDemoPlayerController* PlayerController = Cast<ATxFPSDemoPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideGameOverWidget();
	}
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void UGameOverWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
