// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TXFPSDEMO_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// 该玩家的积分
	UPROPERTY(EditDefaultsOnly, Category = Score)
	float Score = 0.f;

public:
	// Sets default values for this component's properties
	UScoreComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// 给该玩家加分
	void AddScore(float Amount);

	// Getters & Setters
	FORCEINLINE float GetScore() const { return Score; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
