// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class TXFPSDEMO_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* RestartBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitBtn;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* PlayerListBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TotalScoreText;

public:
	virtual void NativeOnInitialized() override;

	void UpdatePlayerListBox(const TArray<TPair<FString, float>>& PlayerScoreList);

protected:
	UFUNCTION()
	void OnRestartClicked();

	UFUNCTION()
	void OnExitClicked();
};
