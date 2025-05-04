// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawnable.h"
#include "SnakeBody.generated.h"


UCLASS()
class SNAKEPROJ_API ASnakeBody : public ASpawnable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SceneComponent", meta = (AllowPrivateAccess = "true"));
	USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* Mesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<ASnakeBody> SnakeBodyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body", meta = (AllowPrivateAccess = "true"));
	int32 PieceID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body", meta = (AllowPrivateAccess = "true"));
	bool bSpawnBody = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body", meta = (AllowPrivateAccess = "true"));
	TWeakObjectPtr<class ASnakePawn> SnakePawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body", meta = (AllowPrivateAccess = "true"));
	TWeakObjectPtr<ASnakeBody> snakeBodyInfront;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body", meta = (AllowPrivateAccess = "true"));
	TWeakObjectPtr<ASnakeBody> snakeBodyBehind;

	FVector NextPosition;
	FVector CurrentPosition;



	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Sets default values for this actor's properties
	ASnakeBody();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "SnakeBody")
	void InitializeSnake(ASnakePawn* pawn, ASnakeBody* Infront, int32 pID, FVector position);

	UFUNCTION(BlueprintCallable, Category = "SnakeBody")
	void SpawnBody();

	UFUNCTION(BlueprintCallable, Category = "SnakeBody")
	void RegisterSnake();
	UFUNCTION(BlueprintCallable, Category = "SnakeBody")
	void MoveBody();

	UFUNCTION(BlueprintCallable, Category = "SnakeBody")
	FORCEINLINE int32 GetPieceID() { return PieceID; };
};
