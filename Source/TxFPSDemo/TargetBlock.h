// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetBlock.generated.h"

UCLASS()
class TXFPSDEMO_API ATargetBlock : public AActor
{
	GENERATED_BODY()

protected:
	// 被打到给玩家加的积分
	UPROPERTY(EditDefaultsOnly, Category = TargetBlock)
	float Score = 5.f;

	// 被打到后自身的缩放倍数
	UPROPERTY(EditDefaultsOnly, Category = TargetBlock)
	float ScaleScalar = 0.75f;

	// 是否是重要目标
	UPROPERTY(EditDefaultsOnly, Category = TargetBlock)
	bool bIsImportantTarget = false;

	// 是否被打到过一次
	bool bIsBeenHit = false;

private:
	// 目标方块的碰撞体组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TargetBlock, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

public:
	// Sets default values for this actor's properties
	ATargetBlock();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Getters
	FORCEINLINE float GetScore() const { return bIsImportantTarget ? 2.f * Score : Score; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 碰撞回调
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	           const FHitResult& Hit);
};
