// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBaseState.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEPROJ_API AGameModeBaseState : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void EnterState();
	virtual void EnterState_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void ExitState();
	virtual void ExitState_Implementation();
};
