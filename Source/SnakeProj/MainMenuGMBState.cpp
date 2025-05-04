// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGMBState.h"

void AMainMenuGMBState::EnterState_Implementation()
{
	//Actually, this gets really hard to do in UE5...probably omitting this idea
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString("ENTER STATE MAINMENU"));
}

void AMainMenuGMBState::ExitState_Implementation()
{

}
