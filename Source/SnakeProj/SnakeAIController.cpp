// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAIController.h"
#include "Apple.h"
#include "SnakeGameStateBase.h"
#include "SnakePawn.h"

constexpr ECollisionChannel Interactable_TC = ECC_GameTraceChannel1;

void ASnakeAIController::BeginPlay()
{
	Super::BeginPlay();
    ASnakeGameStateBase* gameState = Cast<ASnakeGameStateBase>(GetWorld()->GetGameState());
    if (IsValid(gameState))
    {
        CheckFrequency = gameState->GetTimerMax()/5.0f;
        gameState->OnDestroyMap.AddUniqueDynamic(this, &ASnakeAIController::DestroySelf);
    }
}

void ASnakeAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
    ASnakeGameStateBase* gameSate = Cast<ASnakeGameStateBase>(GetWorld()->GetGameState());
    if (IsValid(gameSate))
    {
        gameSate->OnDestroyMap.RemoveDynamic(this, &ASnakeAIController::DestroySelf);
    }
}

void ASnakeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
    snakePawn = Cast<ASnakePawn>(InPawn);
}

void ASnakeAIController::FindApples(FVector position)
{
    TArray<FHitResult> HitResults;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    GetWorld()->SweepMultiByChannel(HitResults, position, position + FVector(0, 0, 50.0f), FQuat::Identity,
        Interactable_TC, FCollisionShape::MakeSphere(50000.0f), QueryParams);
    bool bResult = true;
    bFoundApple = false;
    for (const FHitResult& Hit : HitResults)
    {
        AActor* HitActor = Hit.GetActor();
        AApple* apple = Cast<AApple>(HitActor);

        if (IsValid(apple))
        {
            bFoundApple = true;
            appleLocation = apple->GetActorLocation();
        }
    }
}

void ASnakeAIController::SetNextLocation(FVector position)
{
    if (bFoundApple && snakePawn.IsValid())
    {
        FVector snakePosition = snakePawn->GetActorLocation();
        FVector direction = appleLocation - snakePosition;

        ESnakeMoveDirection previousDirection = snakePawn->GetPreviousDirection();
        ESnakeMoveDirection bestDirection = ESnakeMoveDirection::NONE;
        float bestVectorDirecton = -200.0f;

        float testValue = FVector::DotProduct(direction, FVector(1.0f, 0, 0));
        if (testValue > bestVectorDirecton && (previousDirection != ESnakeMoveDirection::DOWN))
        {
            bestDirection = ESnakeMoveDirection::UP;
            bestVectorDirecton = testValue;
        }

        testValue = FVector::DotProduct(direction, FVector(-1.0f, 0, 0));
        if (testValue > bestVectorDirecton && (previousDirection != ESnakeMoveDirection::UP))
        {
            bestDirection = ESnakeMoveDirection::DOWN;
            bestVectorDirecton = testValue;
        }

        testValue = FVector::DotProduct(direction, FVector(0, 1.0f, 0));
        if (testValue > bestVectorDirecton && (previousDirection != ESnakeMoveDirection::LEFT))
        {
            bestDirection = ESnakeMoveDirection::RIGHT;
            bestVectorDirecton = testValue;
        }
        testValue = FVector::DotProduct(direction, FVector(0, -1.0f, 0));
        if (testValue > bestVectorDirecton && (previousDirection != ESnakeMoveDirection::RIGHT))
        {
            bestDirection = ESnakeMoveDirection::LEFT;
            bestVectorDirecton = testValue;
        }
        snakePawn->SetNextSnakeDirection(bestDirection);

    }
}

void ASnakeAIController::CheckDirection(FVector position, ESnakeMoveDirection MoveDirection)
{

}

void ASnakeAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    timer += DeltaTime;
    if (timer >= CheckFrequency)
    {
        if (snakePawn.IsValid())
        {
            FVector pawnLocation = snakePawn->GetActorLocation();
            FindApples(pawnLocation);
            SetNextLocation(pawnLocation);
        }

    }
}

