// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spawnable.h"
#include "SnakeSelector.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakePawn.generated.h"

UENUM(BlueprintType)
enum class ESnakeMoveDirection : uint8
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

UCLASS()
class SNAKEPROJ_API ASnakePawn : public APawn // Cannot use Spawnable because it's not an interface... uh oh problem. Will have to spaghetti this
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake", meta = (AllowPrivateAccess = "true"))
	USceneComponent* RootSceneComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SnakeBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SnakeNose;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Snake", meta = (AllowPrivateAccess = "true"))
	ESnakeControllerType controllerType = ESnakeControllerType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake")
	ESnakeMoveDirection PreviousDirection = ESnakeMoveDirection::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake")
	ESnakeMoveDirection NextDirection = ESnakeMoveDirection::UP;

	TWeakObjectPtr<class ASnakeGameStateBase> GameStateWPtr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake")
	FVector PreviousPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake")
	FVector NextPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake")
	bool bAlive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake")
	int32 playerID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake")
	TWeakObjectPtr<class ASnakeBody> SnakeBodyBehind;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake")
	bool bSpawnBody = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake")
	TSubclassOf<class ASnakeBody> SnakeBodyClass;



public:
	// Sets default values for this pawn's properties
	ASnakePawn();


	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "snake")
	void SetControllerType(ESnakeControllerType type);
	
	UFUNCTION(BlueprintCallable, Category = "snake")
	void SetNextSnakeDirection(ESnakeMoveDirection direction);

	UFUNCTION(BlueprintCallable, Category = "snake")
	void MoveSnake();

	UFUNCTION(BlueprintCallable, Category = "snake")
	void OnMoveTick();

	UFUNCTION(BlueprintCallable, Category = "snake")
	void OnDestoyMap();

	UFUNCTION(BlueprintCallable, Category = "snake")
	void RegisterSnakePawn();

	UFUNCTION(BlueprintCallable, Category = "snake")
	void InitializePosition(FVector position);
	
	UFUNCTION(BlueprintCallable, Category = "snake")
	FORCEINLINE void SetPlayerID(int32 pID) { this->playerID = pID; };

	UFUNCTION(BlueprintCallable, Category = "snake")
	FORCEINLINE bool IsAlive() { return bAlive; };

	UFUNCTION(BlueprintCallable, Category = "snake")
	FORCEINLINE ESnakeMoveDirection GetPreviousDirection() { return PreviousDirection; };
};
