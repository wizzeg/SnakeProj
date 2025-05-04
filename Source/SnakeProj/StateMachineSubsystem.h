// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StateMachineSubsystem.generated.h"

UENUM(BlueprintType)
enum class EStates : uint8
{
	mainmenu,
	playing,
	paused,
	outro,
	exit,
	none

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, EStates, ExitState, EStates, EnterState);

/**
 * 
 */
UCLASS()
class SNAKEPROJ_API UStateMachineSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	EStates currentState = EStates::mainmenu;

public:
	UPROPERTY(BlueprintAssignable, Category = "StateMachine")
	FOnStateChanged OnStateChanged;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EStates GetCurrentState() { return currentState; }

	UFUNCTION(BlueprintCallable)
	void ChangeState(EStates newState);
	
};
