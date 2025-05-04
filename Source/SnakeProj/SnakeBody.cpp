// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeBody.h"
#include "Spawnable.h"
#include "SnakeGameStateBase.h"
#include "SnakePawn.h"

void ASnakeBody::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (GameStateWPtr.IsValid())
	{
		GameStateWPtr->OnMoveTick.RemoveDynamic(this, &ASnakeBody::MoveBody);
	}
}

// Sets default values
ASnakeBody::ASnakeBody()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>("Root Scene");
	RootComponent = RootSceneComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootSceneComponent);

}

// Called when the game starts or when spawned
void ASnakeBody::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GameStateWPtr.IsValid())
	{
		if (SnakePawn.IsValid())
		{
			if (SnakePawn->IsAlive())
			{
				FVector FramePosition = FMath::Lerp(CurrentPosition, NextPosition, (GameStateWPtr->GetTimer() / FMath::Max(0.0001f, GameStateWPtr->GetTimerMax())));
				SetActorLocation(FramePosition, true);
			}
		}

	}

}

void ASnakeBody::InitializeSnake(ASnakePawn* pawn, ASnakeBody* Infront, int32 pID, FVector position)
{
	FString pIDString = FString::Printf(TEXT("pID: %d"), pID);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, pIDString);
	SnakePawn = pawn;
	PieceID = pID;
	if (PieceID > 1)
	{
		snakeBodyInfront = Infront;
	}
	CurrentPosition = position;
	NextPosition = position;
}

void ASnakeBody::SpawnBody()
{
	if (IsValid(SnakeBodyClass) && !snakeBodyBehind.IsValid())
	{
		bSpawnBody = true;
	}
	else
	{
		if (snakeBodyBehind.IsValid())
		{
			snakeBodyBehind->SpawnBody();
		}
	}
}

void ASnakeBody::RegisterSnake()
{
	if (GameStateWPtr.IsValid())
	{
		GameStateWPtr->OnMoveTick.AddUniqueDynamic(this, &ASnakeBody::MoveBody);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString("SNAKE BODY DID NOT HAVE GAME STATE ON REGISTER"));
	}
}

void ASnakeBody::MoveBody()
{
	if (snakeBodyInfront.IsValid())
	{
		CurrentPosition = NextPosition;
		NextPosition = snakeBodyInfront->GetActorLocation();
	}
	else if (PieceID == 1)
	{
		if (SnakePawn.IsValid())
		{
			CurrentPosition = NextPosition;
			NextPosition = SnakePawn->GetActorLocation();
		}
	}

	if (bSpawnBody)
	{
		ASnakeBody* snakeBody = GetWorld()->SpawnActor<ASnakeBody>(SnakeBodyClass, CurrentPosition, FRotator::ZeroRotator);
		if (IsValid(snakeBody))
		{
			ASnakePawn* snakePawn = SnakePawn.Get();
			if (snakePawn)
			{
				snakeBody->SubscribeOnDestroyMap();
				snakeBody->InitializeSnake(snakePawn, this, (PieceID + 1), GetActorLocation());
				snakeBody->RegisterSnake();
				snakeBodyBehind = snakeBody;
				bSpawnBody = false;
			}
		}
	}
}

