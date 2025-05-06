// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnManager.h"
#include "SnakePawn.h"
#include "SnakeGameStateBase.h"


// Sets default values
APawnManager::APawnManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootSceneComp;

    // Set up Mesh
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    MeshComp->SetupAttachment(RootSceneComp);

    // Set up Spring Arm
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComp->SetupAttachment(MeshComp);
    SpringArmComp->TargetArmLength = 300.0f;  // Adjust distance
    SpringArmComp->bUsePawnControlRotation = false;  // Allow camera rotation

    // Set up Camera
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp);  // Attach camera to Spring Arm

}

void APawnManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
    ASnakeGameStateBase* gameState = Cast<ASnakeGameStateBase>(GetWorld()->GetGameState());
    if (IsValid(gameState))
    {
        gameState->OnDestroyMap.RemoveDynamic(this, &APawnManager::OnDestroyMap);
    }
}

// Called when the game starts or when spawned
void APawnManager::BeginPlay()
{
	Super::BeginPlay();
    ASnakeGameStateBase* gameState = Cast<ASnakeGameStateBase>(GetWorld()->GetGameState());
    if (IsValid(gameState))
    {
        gameState->OnDestroyMap.AddUniqueDynamic(this, &APawnManager::OnDestroyMap);
    }
}

FVector APawnManager::FindCameraPosition()
{
    FVector mean = FVector::ZeroVector;
    int32 numsnakes = 0;
    for (size_t i = 0; i < PlayerPawns.Num(); i++)
    {
        numsnakes++;
        mean += PlayerPawns[i]->GetActorLocation();
    }
    for (size_t i = 0; i < AIPawns.Num(); i++)
    {
        numsnakes++;
        mean += AIPawns[i]->GetActorLocation();
    }
    return (mean / FMath::Max(numsnakes, 1));
}

void APawnManager::MoveCamera(FVector position)
{
    SetActorLocation(position);
}

int32 APawnManager::AddPlayerPawn(APawn* pawn)
{
    GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString("Added Player Pawn"));
    return PlayerPawns.Add(pawn);
}

int32 APawnManager::AddAIPawn(APawn* pawn)
{
    return AIPawns.Add(pawn);
}

void APawnManager::MovePlayer1(ESnakeMoveDirection direction)
{
    if (PlayerPawns.IsValidIndex(0))
    {
        ASnakePawn* snake = Cast<ASnakePawn>(PlayerPawns[0]);
        snake->SetNextSnakeDirection(direction);
    }
}

void APawnManager::MovePlayer2(ESnakeMoveDirection direction)
{
    if (PlayerPawns.IsValidIndex(1))
    {
        ASnakePawn* snake = Cast<ASnakePawn>(PlayerPawns[1]);
        snake->SetNextSnakeDirection(direction);
    }
}

void APawnManager::OnDestroyMap()
{
    PlayerPawns.Empty();
}

// Called every frame
void APawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}