// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainMenuGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEPROJ_API AMainMenuGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UserWidget", meta = (AllowPrivateAcces = "true"));
	UUserWidget* MainMenu = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	void SetMainMenu(UUserWidget* newMainMenu);
	UFUNCTION(BlueprintCallable)
	UUserWidget* GetMainMenu();
};
