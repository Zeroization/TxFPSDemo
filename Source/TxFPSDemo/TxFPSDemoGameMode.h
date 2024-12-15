// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TxFPSDemoGameMode.generated.h"

UCLASS(minimalapi)
class ATxFPSDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// 普通方块类
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = TargetBlock)
	TSubclassOf<class ATargetBlock> BP_NormalTgtBlk;

	// 重要方块类
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = TargetBlock)
	TSubclassOf<class ATargetBlock> BP_ImportantTgtBlk;

	// 生成方块的数量
	UPROPERTY(EditDefaultsOnly, Category = TargetBlock)
	int32 TotalTargetBlockCnt = 10;

	// 生成重要方块的数量
	UPROPERTY(EditDefaultsOnly, Category = TargetBlock)
	int32 ImportantTargetBlockCnt = 4;

protected:
	// GameOver计时器
	FTimerHandle GameOverTimerHandle;
	// GameOver计时器用的倒计时
	UPROPERTY(EditDefaultsOnly, Category = GameOver)
	float GameOverInterval = 10.f;

public:
	ATxFPSDemoGameMode();

protected:
	virtual void BeginPlay() override;

	void OnCountDown();
	void OnGameOver();
};
