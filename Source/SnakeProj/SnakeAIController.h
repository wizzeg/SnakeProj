// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SnakePawn.h"
#include "SnakeAIController.generated.h"

//constexpr ECollisionChannel Interactable_TC = ECC_GameTraceChannel1;
/**
 * 
 */

//TODO: Obstacle avoidance
UCLASS()
class SNAKEPROJ_API ASnakeAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"));
	bool bFoundApple = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"));
	FVector appleLocation = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"));
	float CheckFrequency = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"));
	float timer = 0.0f;

	TWeakObjectPtr<class ASnakePawn> snakePawn;
	

	void BeginPlay() override;


	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void FindApples(FVector position);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetNextLocation(FVector position);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void CheckDirection(FVector position, ESnakeMoveDirection MoveDirection);

	UFUNCTION(BlueprintCallable, Category = "AI")
	FORCEINLINE void DestroySelf() { Destroy(); };

	bool DoLineTrace(FVector start, FVector direction);

public:
	void Tick(float DeltaTime) override;

};
