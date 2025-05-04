// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeBaseState.h"
#include "MainMenuGMBState.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEPROJ_API AMainMenuGMBState : public AGameModeBaseState
{
	GENERATED_BODY()
	
public:
	void EnterState_Implementation() override;
	void ExitState_Implementation() override;
};
