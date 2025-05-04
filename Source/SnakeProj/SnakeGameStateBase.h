// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SnakeGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAppleEaten, int32, PlayerID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyMap);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveTick);
/**
 * 
 */
UCLASS()
class SNAKEPROJ_API ASnakeGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable", meta = (AllowPrivateAccess = "true"))
	int32 Player1Score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable", meta = (AllowPrivateAccess = "true"))
	int32 Player2Score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable", meta = (AllowPrivateAccess = "true"))
	int32 ApplesEaten = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable", meta = (AllowPrivateAccess = "true"))
	int32 ApplesToEat = 2;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASnakePawn> SnakePawnClass = nullptr;

    UPROPERTY(BlueprintAssignable, Category="Events")
    FOnAppleEaten OnAppleEaten;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnDestroyMap OnDestroyMap;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnMoveTick OnMoveTick;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Snakes", meta = (AllowPrivateAccess = "true"))
	TArray<class ASnakePawn*> SnakePawns;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Snakes", meta = (AllowPrivateAccess = "true"))
	class APawn* PawnManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Controllers", meta = (AllowPrivateAccess = "true"))
	TArray<class ASnakeAIController*> AIControllers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	float timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	float timerMax = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	bool bStartTick = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAccess = "true"))
	int32 MaxMaps = 2;

public:
	FORCEINLINE void AddSnakePawn(class ASnakePawn* snake) { SnakePawns.Add(snake); }
	void AddSnakePawns(TArray<class ASnakePawn*> snakes);
	FORCEINLINE class ASnakePawn* GetSnakePawnAtIndex(int32 index) { return (index < SnakePawns.Num() ? SnakePawns[index] : nullptr); }

	FORCEINLINE void AddSnakePawn(class ASnakeAIController* AIController) { AIControllers.Add(AIController); }
	FORCEINLINE class ASnakeAIController* GetAIControllerAtIndex(int32 index) { return (index < AIControllers.Num() ? AIControllers[index] : nullptr); }

	UFUNCTION(BlueprintCallable, Category = "Init")
	FORCEINLINE void SetPawnManager(class APawn* manager) { PawnManager = manager; }
	FORCEINLINE APawn* GetPawnManager() { return PawnManager; }

	UFUNCTION(BlueprintCallable, Category = "Event")
	void TriggerOnAppleEaten(int32 playerID);

	UFUNCTION(BlueprintCallable, Category = "Event")
	void TriggerOnDestroyMap();

	UFUNCTION(BlueprintCallable, Category = "Event")
	void AppleEaten(int32 playerID);

	UFUNCTION(BlueprintCallable, Category = "Variables")
	FORCEINLINE int32 GetApplesEaten() { return ApplesEaten; };

	UFUNCTION(BlueprintCallable, Category = "Variables")
	FORCEINLINE int32 GetApplesToEat() { return ApplesToEat; };

	UFUNCTION(BlueprintCallable, Category = "Event")
	FORCEINLINE void TimerTick(float dt) { if (bStartTick) { timer += dt; } if (timer >= timerMax) { timer = 0.0f; TriggerMoveTick(); } };

	UFUNCTION(BlueprintCallable, Category = "Timer")
	FORCEINLINE void StartTick() { bStartTick = true; timer = 0.0f; };

	UFUNCTION(BlueprintCallable, Category = "Timer")
	FORCEINLINE void StopTick() { bStartTick = false; timer = 0.0f; };

	UFUNCTION(BlueprintCallable, Category = "Timer")
	FORCEINLINE void TriggerMoveTick() { OnMoveTick.Broadcast(); };

	UFUNCTION(BlueprintCallable, Category = "Timer")
	FORCEINLINE float GetTimer() { return timer; };

	UFUNCTION(BlueprintCallable, Category = "Timer")
	FORCEINLINE float GetTimerMax() { return timerMax; };

	UFUNCTION(BlueprintCallable, Category = "Snakes")
	FVector GetSnakesAvergePosition();

	UFUNCTION(BlueprintCallable, Category = "Variables")
	FORCEINLINE int32 GetMaxMaps() { return MaxMaps; };


};
