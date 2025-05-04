// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeManagerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "PawnManager.h"
#include "SnakeGameStateBase.h"

void ASnakeManagerController::MovePlayer1(ESnakeMoveDirection direction) // should probably added an int to choose player instead
{
	APawn* pawn = GetPawn();
	if (pawn)
	{
		APawnManager* pawnManager = Cast<APawnManager>(pawn);
		if (pawnManager)
		{
			pawnManager->MovePlayer1(direction);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Snake1Pawn not found"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Snake1Pawn not found"));
	}
}

void ASnakeManagerController::MovePlayer2(ESnakeMoveDirection direction)
{
	APawn* pawn = GetPawn();
	if (pawn)
	{
		APawnManager* pawnManager = Cast<APawnManager>(pawn);
		if (pawnManager)
		{
			pawnManager->MovePlayer2(direction);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Snake2Pawn not found"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Snake2Pawn not found"));
	}
}

void ASnakeManagerController::SetUpInput()
{
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	FString PlayerInfo = FString::Printf(TEXT("Local Player: %s"), *GetLocalPlayer()->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, PlayerInfo);

	int32 numPlayers = GetGameInstance()->GetNumLocalPlayers();
	FString NumerPlayers = FString::Printf(TEXT("Number of players: %d"), numPlayers);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, NumerPlayers);
	if (InputSubsystem && InputMappingContext)
	{
		InputSubsystem->AddMappingContext(InputMappingContext, 0);
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, FString("Added InputMappingContexted from Cpp"));
	}
}

void ASnakeManagerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	ASnakeGameStateBase* gameState = Cast<ASnakeGameStateBase>(GetWorld()->GetGameState());
	if (gameState)
	{
		AActor* managerPawn = GetPawn();
		managerPawn->SetActorLocation((gameState->GetSnakesAvergePosition() + FVector(0,0,200.0f)));
	}
}
