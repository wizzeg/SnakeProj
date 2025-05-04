// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakePawn.h"
#include "Spawnable.h"
#include "SnakeGameStateBase.h"
#include "Apple.h"
#include "SnakeBody.h"
#include "Wall.h"


// Sets default values
ASnakePawn::ASnakePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootScene");
	RootComponent = RootSceneComp;

	SnakeBody = CreateDefaultSubobject<UStaticMeshComponent>("MeshBody");
	SnakeBody->SetupAttachment(RootSceneComp);


	SnakeNose = CreateDefaultSubobject<UStaticMeshComponent>("MeshNose");
	SnakeNose->SetupAttachment(SnakeBody);
	// this seems to give 0,0,0...
	//NextPosition = GetActorLocation();
	//PreviousPosition = NextPosition;
}

void ASnakePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GameStateWPtr.IsValid())
	{
		GameStateWPtr->OnDestroyMap.RemoveDynamic(this, &ASnakePawn::OnDestoyMap);
		GameStateWPtr->OnMoveTick.RemoveDynamic(this, &ASnakePawn::OnMoveTick);
	}
	Super::EndPlay(EndPlayReason);
}

void ASnakePawn::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AApple* apple = Cast<AApple>(OtherActor);
	if (IsValid(apple))
	{
		if (apple->EatApple(playerID))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString("Apple Eaten!"));
			if (SnakeBodyBehind.IsValid())
			{
				SnakeBodyBehind->SpawnBody();
			}
			else
			{
				bSpawnBody = true;
			}
		}
	}

	AWall* wall = Cast<AWall>(OtherActor);
	if (IsValid(wall))
	{
		bAlive = false;
	}
	ASnakeBody* snakeBody = Cast<ASnakeBody>(OtherActor);
	if (IsValid(snakeBody))
	{
		if (snakeBody->GetPieceID() <= 1)
		{
			if (SnakeBodyBehind.IsValid())
			{
				if (snakeBody != SnakeBodyBehind.Get())
				{
					bAlive = false;
				}
			}
		}
		else
		{
			bAlive = false;
		}
	}
	ASnakePawn* snakePawn = Cast<ASnakePawn>(OtherActor);
	if (IsValid(snakePawn))
	{
		bAlive = false;
	}
}

// Called when the game starts or when spawned
void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakePawn::Tick(float DeltaTime)
{
	if (bAlive)
	{
		MoveSnake();
	}
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASnakePawn::SetControllerType(ESnakeControllerType type)
{
	controllerType = type;
}

void ASnakePawn::SetNextSnakeDirection(ESnakeMoveDirection direction)
{
	switch (direction) // This is kinda bad though, should have made it into an FVector so we can use dot product
	{
	case ESnakeMoveDirection::UP:
		if (PreviousDirection != ESnakeMoveDirection::DOWN)
		{
			NextDirection = direction;
		}
		break;
	case ESnakeMoveDirection::DOWN:
		if (PreviousDirection != ESnakeMoveDirection::UP)
		{
			NextDirection = direction;
		}
		break;
	case ESnakeMoveDirection::LEFT:
		if (PreviousDirection != ESnakeMoveDirection::RIGHT)
		{
			NextDirection = direction;
		}
		break;
	case ESnakeMoveDirection::RIGHT:
		if (PreviousDirection != ESnakeMoveDirection::LEFT)
		{
			NextDirection = direction;
		}
		break;
	case ESnakeMoveDirection::NONE:
		break;
	default:
		break;
	}
}

void ASnakePawn::MoveSnake()
{
	if (GameStateWPtr.IsValid())
	{
		FVector FramePosition = FMath::Lerp(PreviousPosition, NextPosition, (GameStateWPtr->GetTimer() / FMath::Max(0.0001f, GameStateWPtr->GetTimerMax())));
		SetActorLocation(FramePosition, true);
		FVector ForwardVector;
		switch (NextDirection)
		{
		case ESnakeMoveDirection::UP:
			ForwardVector = FVector(1.0f,0,0);
			break;
		case ESnakeMoveDirection::DOWN:
			ForwardVector = FVector(-1.0f, 0, 0);
			break;
		case ESnakeMoveDirection::LEFT:
			ForwardVector = FVector(0, -1.0f, 0);
			break;
		case ESnakeMoveDirection::RIGHT:
			ForwardVector = FVector(0, 1.0f, 0);
			break;
		case ESnakeMoveDirection::NONE:
			break;
		default:
			break;
		}

		FRotator TargetRotation = FRotationMatrix::MakeFromX(ForwardVector).Rotator();

		FRotator CurrentRotation = GetActorRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GameStateWPtr->GetTimer(), 0.1f); // 2.0f is interp speed

		SetActorRotation(NewRotation);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("GameStateWPtr not valid"));
	}
	
}

void ASnakePawn::OnMoveTick()
{
	if (bAlive)
	{
		if (bSpawnBody)
		{
			if (IsValid(SnakeBodyClass))
			{
				ASnakeBody* snakebody = GetWorld()->SpawnActor<ASnakeBody>(SnakeBodyClass, GetActorLocation(), FRotator::ZeroRotator);
				if (IsValid(snakebody))
				{
					SnakeBodyBehind = snakebody;
					snakebody->SubscribeOnDestroyMap();
					snakebody->InitializeSnake(this, snakebody, 1, GetActorLocation());
					snakebody->RegisterSnake();
					bSpawnBody = false;
				}
			}
		}
		PreviousPosition = NextPosition;
		switch (NextDirection)
		{
		case ESnakeMoveDirection::UP:
			NextPosition = PreviousPosition + FVector(100.0f, 0, 0); // prone to float precision issues, bad system (but could routinely calculate exact position)
			break;
		case ESnakeMoveDirection::DOWN:
			NextPosition = PreviousPosition + FVector(-100.0f, 0, 0);
			break;
		case ESnakeMoveDirection::LEFT:
			NextPosition = PreviousPosition + FVector(0, -100.0f, 0);
			break;
		case ESnakeMoveDirection::RIGHT:
			NextPosition = PreviousPosition + FVector(0, 100.0f, 0);
			break;
		case ESnakeMoveDirection::NONE:
			break;
		default:
			break;
		}
		PreviousDirection = NextDirection;
	}
}

void ASnakePawn::OnDestoyMap()
{
	Destroy();
}

void ASnakePawn::RegisterSnakePawn()
{
	ASnakeGameStateBase* snakeGameState = Cast<ASnakeGameStateBase>(GetWorld()->GetGameState());
	if (snakeGameState)
	{
		GameStateWPtr = snakeGameState;
		GameStateWPtr->OnDestroyMap.AddUniqueDynamic(this, &ASnakePawn::OnDestoyMap);
		GameStateWPtr->OnMoveTick.AddUniqueDynamic(this, &ASnakePawn::OnMoveTick);
	}
}

void ASnakePawn::InitializePosition(FVector position)
{
	NextPosition = position;
	PreviousPosition = position;
}

