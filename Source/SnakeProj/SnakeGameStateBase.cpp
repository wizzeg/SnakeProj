// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeGameStateBase.h"
#include "SnakePawn.h"

void ASnakeGameStateBase::AddSnakePawns(TArray<ASnakePawn*> snakes)
{
	for (size_t i = 0; i < snakes.Num(); i++)
	{
		SnakePawns.Add(snakes[i]);
	}
}

void ASnakeGameStateBase::TriggerOnAppleEaten(int32 playerID)
{
	AppleEaten(playerID);
	OnAppleEaten.Broadcast(playerID);

}

void ASnakeGameStateBase::TriggerOnDestroyMap()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Silver, FString("DestroyMapCalled"));
	SnakePawns.Empty();
	SnakesAlive = 0;
	//bStartTick = false;
	//timer = 0.0f;
	StopTick();
	ApplesEaten = 0;
	OnDestroyMap.Broadcast();
	ApplesEaten = 0;

}

void ASnakeGameStateBase::AppleEaten(int32 playerID) // this will bind first, and be called first.
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString("GameState got Apple Eaten"));
	bool bValidPlayerID = true;
	if (playerID == 1)
	{
		Player1Score++;
	}
	else if (playerID == 2) // this could also be invalid, but whatever.
	{
		Player2Score++;
	}
	else
	{
		bValidPlayerID = false;
	}
	ApplesEaten++;
	GEngine->AddOnScreenDebugMessage(-1, 10,FColor::Silver, FString::Printf(TEXT("Scores are : %d %d, with total apples eaten %d"), Player1Score, Player2Score, ApplesEaten));
	if (ApplesEaten >= ApplesToEat)
	{
		ApplesEaten = 0;
		TriggerOnDestroyMap();
	}
}

FVector ASnakeGameStateBase::GetSnakesAvergePosition()
{
	FVector AveragePosition = FVector::ZeroVector;
	for (size_t i = 0; i < SnakePawns.Num(); i++)
	{
		if (SnakePawns[i].IsValid())
		{
			AveragePosition += SnakePawns[i]->GetActorLocation();
		}
	}
	if (SnakePawns.Num() > 0)
	{
		return AveragePosition / SnakePawns.Num();
	}
	return FVector::ZeroVector;
}

void ASnakeGameStateBase::TriggerSnakesDead()
{
	OnSnakesDead.Broadcast();
}

void ASnakeGameStateBase::SnakeDied()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Silver, FString("SnakeDied"));
	SnakesAlive--;
	if (SnakesAlive <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Silver, FString("All snakes dead"));
		SnakesAlive = 0;
		TriggerSnakesDead();
	}
}
