// Fill out your copyright notice in the Description page of Project Settings.
#include "SnakeGameMode.h"
#include "SnakePawn.h"
#include "SnakeGameStateBase.h"
#include "WorldGenActor.h"
#include "SnakeAIController.h"
#include "PawnManager.h"

void ASnakeGameMode::CreateSnakes(TArray<ESnakeControllerType> types, TArray<FVector> positions)
{
	ASnakeGameStateBase* SnakeGameState = GetWorld()->GetGameState<ASnakeGameStateBase>();
	if (!SnakeGameState) return;

	if (!SnakePawnClass)
	{
		if (SnakeGameState)
		{
			SnakePawnClass = SnakeGameState->SnakePawnClass;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Failed getting Pawn class"));
		}
	}
	int32 AIControllerNum = 0;
	if (SnakePawnClass)
	{
		int32 snakeNum = 0;
		for (size_t i = 0; i < types.Num(); i++)
		{
			if (types[i] != ESnakeControllerType::NONE)
			{
				FVector position = FVector::ZeroVector;
				if (positions.IsValidIndex(snakeNum))
				{
					GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString("Snake position is chosen yes!!!!!!!!!!"));
					position = positions[snakeNum];
				}
				GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Green, FString("Spawned snake"));
				ASnakePawn* snake = GetWorld()->SpawnActor<ASnakePawn>(SnakePawnClass, position, FRotator::ZeroRotator);

				GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, position.ToString());
				if (snake)
				{
					snake->InitializePosition(position);
					snake->RegisterSnakePawn();
					snake->SetControllerType(types[i]);
					snake->SetPlayerID(snakeNum + 1); // spawns need to be placed in order, player 1 need to spawn above player 2... Or maybe not.I don't know, and I don't care at this point
					SnakeGameState->AddAliveSnake();
					SnakeGameState->AddSnakePawn(snake);
					if (types[i] == ESnakeControllerType::AI)
					{
						if (SnakeAIControllerClass && !bAIControllersCreated)
						{
							ASnakeAIController* AIController = GetWorld()->SpawnActor<ASnakeAIController>(SnakeAIControllerClass);
							AIController->Possess(snake);
							AIControllers.Add(AIController);
							snakeNum++;
						}
						else if (SnakeAIControllerClass)
						{
							AIControllers[AIControllerNum++]->Possess(snake);
						}
						else
						{
							GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("No SnakeAIControllerClass (to spawn)"));
						}
					}
					else if (types[i] == ESnakeControllerType::HUMAN)
					{
						APawnManager* manager = Cast<APawnManager>(SnakeGameState->GetPawnManager());
						if (manager)
						{
							manager->AddPlayerPawn(snake);
							GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString("Added PlayerSnake"));
							snakeNum++;
						}
						else GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Failed to get manager"));
					}
				}
			}
		}
		bAIControllersCreated = true;
		SnakeGameState->OnDestroyMap.AddUniqueDynamic(this, &ASnakeGameMode::OnDestroyMap);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Failed getting Pawn class (no spawnininb)"));
	}
}

void ASnakeGameMode::NextMap(int32 mapNum)
{
	if (IsValid(WorldGenerator))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, FString("Spawning Map!"));
		Cast<AWorldGenActor>(WorldGenerator)->DestroyMap();
		Cast<AWorldGenActor>(WorldGenerator)->GenerateMap(mapNum);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString("WorldGenerator doesn't exist???"));
	}
}



void ASnakeGameMode::SpawnMapGenActor()
{
	if (WorldGenerator) WorldGenerator->Destroy();
	WorldGenerator = GetWorld()->SpawnActor<AWorldGenActor>(WorldGenClass, FVector::ZeroVector, FRotator::ZeroRotator);
	UE_LOG(LogTemp, Warning, TEXT("WorldGenerator: %s"), *GetNameSafe(WorldGenerator));
}



void ASnakeGameMode::AppleEaten(int32 playerID)
{
	ASnakeGameStateBase* gameState = Cast<ASnakeGameStateBase>(GameState);
	int32 applesToEat = gameState->GetApplesToEat();
	int32 applesEaten = gameState->GetApplesEaten();

	if (applesEaten < applesToEat && applesEaten != 0) // basically "race condition" on the events, need to do this ugly thing or redesign a lot, and I'm not doing the latter now
	{
		if (WorldGenerator)
		{
			AWorldGenActor* worldGen = Cast<AWorldGenActor>(WorldGenerator);
			worldGen->SpawnApple();
		}

	}
	//else // this is a delegate race condition, we'll handle it in snakegamestatebase instead
	//{
	//	gameState->TriggerOnDestroyMap();
	//}
}

void ASnakeGameMode::OnSnakesDead() // Blueprints vs C++ has kind collapsed by this point, C++ is just much faster, Blueprints are neat but slows down.
{
	ASnakeGameStateBase* SnakeGameState = GetWorld()->GetGameState<ASnakeGameStateBase>();
	if (IsValid(SnakeGameState))
	{
		SnakeGameState->TriggerOnDestroyMap();
	}
}

void ASnakeGameMode::SubscribeOnSnakesDead()
{
	ASnakeGameStateBase* gameState = Cast<ASnakeGameStateBase>(GameState);
	if (gameState)
	{
		gameState->OnSnakesDead.AddUniqueDynamic(this, &ASnakeGameMode::OnSnakesDead);
	}
}

void ASnakeGameMode::OnDestroyMap()
{
	AIControllers.Empty();
	ASnakeGameStateBase* SnakeGameState = GetWorld()->GetGameState<ASnakeGameStateBase>();
	//CurrentMapNum++;
	bAIControllersCreated = false;
	if (!SnakeGameState) return;
	SnakeGameState->OnDestroyMap.RemoveDynamic(this, &ASnakeGameMode::OnDestroyMap);
}


