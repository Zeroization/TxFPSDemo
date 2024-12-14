// Copyright Epic Games, Inc. All Rights Reserved.

#include "TxFPSDemoGameMode.h"

#include "ScoreComponent.h"
#include "TargetBlock.h"
#include "TxFPSDemoCharacter.h"
#include "TimerManager.h"
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
	GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ATxFPSDemoGameMode::OnGameOver,
	                                GameOverInterval);
}

void ATxFPSDemoGameMode::OnGameOver()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "====GAME OVER====");
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "  NAME     SCORE ");

		// 统计每个玩家的分数和总分数
		float TotalScore = 0.f;
		for (APlayerState* PlayerState : GetGameState<AGameStateBase>()->PlayerArray)
		{
			ATxFPSDemoCharacter* Player = Cast<ATxFPSDemoCharacter>(PlayerState->GetPlayerController()->GetCharacter());
			if (Player != nullptr)
			{
				float Score = Player->GetScoreComponent()->GetScore();
				FString TmpMsg = PlayerState->GetName() + FString::Printf(TEXT("    %f"), Score);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TmpMsg);
				TotalScore += Score;
			}
		}
		FString TmpMsg = FString::Printf(TEXT("Total Score: %f"), TotalScore);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TmpMsg);
	}
}
