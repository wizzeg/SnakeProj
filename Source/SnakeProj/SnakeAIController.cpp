// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAIController.h"
#include "Apple.h"
#include "SnakeGameStateBase.h"
#include "SnakePawn.h"
#include "Wall.h"
#include "SnakeBody.h"



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
        ECC_GameTraceChannel1, FCollisionShape::MakeSphere(50000.0f), QueryParams);
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

        FVector ActorLocation = GetPawn()->GetActorLocation();

        float testValue = FVector::DotProduct(direction, FVector(1.0f, 0, 0));
        if (testValue > bestVectorDirecton && (previousDirection != ESnakeMoveDirection::DOWN) && DoLineTrace(ActorLocation, FVector(1.0f, 0, 0)))
        {
            bestDirection = ESnakeMoveDirection::UP;
            bestVectorDirecton = testValue;
        }

        testValue = FVector::DotProduct(direction, FVector(-1.0f, 0, 0));
        if (testValue > bestVectorDirecton && (previousDirection != ESnakeMoveDirection::UP) && DoLineTrace(ActorLocation, FVector(-1.0f, 0, 0)))
        {
            bestDirection = ESnakeMoveDirection::DOWN;
            bestVectorDirecton = testValue;
        }

        testValue = FVector::DotProduct(direction, FVector(0, 1.0f, 0));
        if (testValue > bestVectorDirecton && (previousDirection != ESnakeMoveDirection::LEFT) && DoLineTrace(ActorLocation, FVector(0, 1.0f, 0)))
        {
            bestDirection = ESnakeMoveDirection::RIGHT;
            bestVectorDirecton = testValue;
        }
        testValue = FVector::DotProduct(direction, FVector(0, -1.0f, 0));
        if (testValue > bestVectorDirecton && (previousDirection != ESnakeMoveDirection::RIGHT) && DoLineTrace(ActorLocation, FVector(0, -1.0f, 0)))
        {
            bestDirection = ESnakeMoveDirection::LEFT;
            bestVectorDirecton = testValue;
        }
        if (bestDirection == ESnakeMoveDirection::NONE)
        {
            bestDirection = ESnakeMoveDirection::UP;
        }
        snakePawn->SetNextSnakeDirection(bestDirection);

    }
}

void ASnakeAIController::CheckDirection(FVector position, ESnakeMoveDirection MoveDirection)
{

}

bool ASnakeAIController::DoLineTrace(FVector Start, FVector Direction)
{
    bool bResult = true;
    TArray<FHitResult> HitResults;

    FCollisionShape CollisionShape = FCollisionShape::MakeSphere(10.0f); // Small detection radius

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetPawn());

    bool bHit = GetWorld()->LineTraceMultiByChannel(
        HitResults,
        Start + FVector(0,0,10),
        FVector(0, 0, 10) + Start + Direction * 120,
        ECC_GameTraceChannel2,
        QueryParams
    );


	for (const FHitResult& Hit : HitResults)
	{
        // no other way, tracing does not behave as one would expect. bHit doesn't work, becuase block in profile doens't block, for whatever reason, jesus christ.
        // This whole project is absolutely cursed, do not look too deep into it, I don't know what will happen to you if you do.
		if (Cast<AWall>(Hit.GetActor())) 
        {
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, FString("Found Actor"));
			bResult = false;
		}
		else if (Cast<APawn>(Hit.GetActor()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, FString("Found Actor"));
			bResult = false;
		}
        else if (Cast<ASnakeBody>(Hit.GetActor()))
        {
            GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, FString("Found Actor"));
            bResult = false;
        }
	}

    DrawDebugLine(
        GetWorld(),
        Start + FVector(0, 0, 10),
        Start + FVector(0, 0, 10) + Direction * 120,
        FColor::Red,   // Line color
        false,         // Persistent? Set to true if you want it to stay
        0.2f,          // Lifetime (in seconds)
        0,             // Depth priority
        2.0f           // Thickness
    );

    return bResult;
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

