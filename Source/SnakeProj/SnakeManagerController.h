// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnakePawn.h"
#include "SnakeManagerController.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEPROJ_API ASnakeManagerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputMapping")
	class UInputMappingContext* InputMappingContext;

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void MovePlayer1(ESnakeMoveDirection direction);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MovePlayer2(ESnakeMoveDirection direction);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetUpInput();


	void PlayerTick(float DeltaTime) override;

};
