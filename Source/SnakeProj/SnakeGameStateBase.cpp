// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeGameStateBase.h"
#include "SnakePawn.h"

void ASnakeGameStateBase::AddSnakePawns(TArray<class ASnakePawn*> snakes)
{
	for (size_t i = 0; i < snakes.Num(); i++)
	{
		SnakePawns.Add(snakes[i]);
	}
}

void ASnakeGameStateBase::TriggerOnAppleEaten(int32 playerID)
{
	OnAppleEaten.Broadcast(playerID);
	AppleEaten(playerID);
}

void ASnakeGameStateBase::TriggerOnDestroyMap()
{
	OnDestroyMap.Broadcast();
	SnakePawns.Empty();
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
}

FVector ASnakeGameStateBase::GetSnakesAvergePosition()
{
	FVector AveragePosition = FVector::ZeroVector;
	for (size_t i = 0; i < SnakePawns.Num(); i++)
	{
		AveragePosition += SnakePawns[i]->GetActorLocation();
	}
	if (SnakePawns.Num() > 0)
	{
		return AveragePosition / SnakePawns.Num();
	}
	return FVector::ZeroVector;
}
