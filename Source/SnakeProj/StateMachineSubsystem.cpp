// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineSubsystem.h"

void UStateMachineSubsystem::ChangeState(EStates newState)
{
	//if (newState == currentState) return;

	OnStateChanged.Broadcast(currentState, newState);
	currentState = newState;
}
