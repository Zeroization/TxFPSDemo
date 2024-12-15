// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreComponent.h"

#include "GameplayInterface.h"


// Sets default values for this component's properties
UScoreComponent::UScoreComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UScoreComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UScoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UScoreComponent::AddScore(float Amount)
{
	Score += Amount;

	// 执行OnGetScore()接口
	if (GetOwner()->Implements<UGameplayInterface>())
	{
		IGameplayInterface::Execute_OnGetScore(GetOwner());
	}
}
