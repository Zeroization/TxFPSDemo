// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "GameplayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TXFPSDEMO_API IGameplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 玩家获得积分后的回调
	UFUNCTION(BlueprintNativeEvent, Category = Score)
	void OnGetScore();
	virtual void OnGetScore_Implementation() = 0;
};
