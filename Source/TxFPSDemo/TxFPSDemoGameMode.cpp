// Copyright Epic Games, Inc. All Rights Reserved.

#include "TxFPSDemoGameMode.h"

#include "ScoreComponent.h"
#include "TargetBlock.h"
#include "TxFPSDemoCharacter.h"
#include "TimerManager.h"
#include "TxFPSDemoPlayerController.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

ATxFPSDemoGameMode::ATxFPSDemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void ATxFPSDemoGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 随机生成N个方块
	ImportantTargetBlockCnt = (ImportantTargetBlockCnt > TotalTargetBlockCnt)
		                          ? TotalTargetBlockCnt
		                          : ImportantTargetBlockCnt;
	for (int32 i = 1; i <= TotalTargetBlockCnt; ++i)
	{
		// 随机生成方块的位置
		FVector Origin(1500.f, 1500.f, 400.f);
		FVector Extents(1250.f, 1250.f, 0.f);
		float RandomX = FMath::RandRange(Origin.X - Extents.X, Origin.X + Extents.X);
		float RandomY = FMath::RandRange(Origin.Y - Extents.Y, Origin.Y + Extents.Y);

		FVector SpawnLocation(RandomX, RandomY, Origin.Z);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		if (i <= ImportantTargetBlockCnt)
		{
			GetWorld()->SpawnActor<ATargetBlock>(BP_ImportantTgtBlk, SpawnLocation, SpawnRotation);
		}
		else
		{
			GetWorld()->SpawnActor<ATargetBlock>(BP_NormalTgtBlk, SpawnLocation, SpawnRotation);
		}
	}

	// 初始化游戏结算计时器
	GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ATxFPSDemoGameMode::OnCountDown,
	                                1.0f, true);
}

void ATxFPSDemoGameMode::OnCountDown()
{
	--GameOverInterval;

	// 更新所有玩家的HUD
	for (APlayerState* PlayerState : GetGameState<AGameStateBase>()->PlayerArray)
	{
		ATxFPSDemoPlayerController* PlayerController = Cast<ATxFPSDemoPlayerController>(
			PlayerState->GetPlayerController());
		if (PlayerController != nullptr)
		{
			PlayerController->UpdateCountdown(GameOverInterval);
		}
	}

	if (GameOverInterval <= 0)
	{
		GetWorldTimerManager().ClearTimer(GameOverTimerHandle);
		OnGameOver();
	}
}

void ATxFPSDemoGameMode::OnGameOver()
{
	TArray<TPair<FString, float>> PlayerScoreList;
	for (APlayerState* PlayerState : GetGameState<AGameStateBase>()->PlayerArray)
	{
		ATxFPSDemoCharacter* Player = Cast<ATxFPSDemoCharacter>(PlayerState->GetPlayerController()->GetCharacter());
		if (Player != nullptr)
		{
			FString Name = PlayerState->GetName();
			float Score = Player->GetScoreComponent()->GetScore();
			PlayerScoreList.Add({Name, Score});
		}
	}
	PlayerScoreList.Sort([](const TPair<FString, float>& A, const TPair<FString, float>& B)
	{
		return A.Value > B.Value;
	});

	for (APlayerState* PlayerState : GetGameState<AGameStateBase>()->PlayerArray)
	{
		ATxFPSDemoPlayerController* PlayerController = Cast<ATxFPSDemoPlayerController>(
			PlayerState->GetPlayerController());
		if (PlayerController != nullptr)
		{
			PlayerController->ShowGameOverWidget(PlayerScoreList);
		}
	}
}
