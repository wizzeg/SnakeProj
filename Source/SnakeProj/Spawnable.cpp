// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawnable.h"
#include "SnakeGameStateBase.h"
#include "WorldGenActor.h"


// Sets default values
ASpawnable::ASpawnable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpawnable::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (SpawnerPtr.IsValid())
	{
		SpawnerPtr->OnDestroyWorld.RemoveDynamic(this, &ASpawnable::DestroySelf);
	}
	if (GameStateWPtr.IsValid())
	{
		GameStateWPtr->OnDestroyMap.RemoveDynamic(this, &ASpawnable::DestroySelf);
	}
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ASpawnable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnable::SubscribeToOnDestroyWorld(class AWorldGenActor* WorldGenerator) // not used anymore
{
	SubscribeOnDestroyMap();
	//if (WorldGenerator)
	//{
	//	SpawnerPtr = WorldGenerator;
	//	SpawnerPtr->OnDestroyWorld.AddUniqueDynamic(this, &ASpawnable::DestroySelf);
	//}
}

void ASpawnable::SubscribeOnDestroyMap()
{
	ASnakeGameStateBase* gameState = Cast<ASnakeGameStateBase>(GetWorld()->GetGameState());
	if (gameState)
	{
		GameStateWPtr = gameState;
		GameStateWPtr->OnDestroyMap.AddUniqueDynamic(this, &ASpawnable::DestroySelf);
	}
}

