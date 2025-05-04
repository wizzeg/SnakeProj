// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameStateBase.h"

void AMainMenuGameStateBase::SetMainMenu(UUserWidget* newMainMenu)
{
	MainMenu = newMainMenu;
}

UUserWidget* AMainMenuGameStateBase::GetMainMenu()
{
	return MainMenu;
}
