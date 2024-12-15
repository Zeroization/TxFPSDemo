// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TxFPSDemoPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class TXFPSDEMO_API ATxFPSDemoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_HUDWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameOverWidget> BP_GameOverWidget;

protected:
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

private:
	UPROPERTY()
	class UHUDWidget* HUDWidget;

	UPROPERTY()
	class UGameOverWidget* GameOverWidget;

public:
	// HUD Widget
	void UpdateCurrentScore(float NewScore);
	void UpdateCountdown(float NewCountdown);

	// GameOver Widget
	void ShowGameOverWidget(const TArray<TPair<FString, float>>& PlayerScoreList);
	void HideGameOverWidget();

protected:
	virtual void BeginPlay() override;
};
