// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "SnakeSelector.h"
#include "Engine/GameInstance.h"
#include "SnakeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEPROJ_API USnakeGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controllers", meta = (AllowPrivateAcces = "true"))
	TArray<ESnakeControllerType> ControllerTypes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scores", meta = (AllowPrivateAcces = "true"))
	TArray<int32> Scores = {0, 0};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameMode", meta = (AllowPrivateAcces = "true"))
	bool bIsCoop = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameMode", meta = (AllowPrivateAcces = "true"))
	int32 ApplesToEat = 10;

public:
	UFUNCTION(BlueprintCallable)
	void AddSnakeControllers(TArray<ESnakeControllerType> types);

	UFUNCTION(BlueprintCallable)
	void ClearSnakeControllers();

	UFUNCTION(BlueprintCallable)
	TArray<ESnakeControllerType> GetControllerTypes();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<int32> GetScores() { return Scores; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetScoresAtIndex(int32 index, int32 score) { Scores[index] = score; };

	UFUNCTION(BlueprintCallable)
	void ResetGame();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetApplesToEat(int32 amount) { ApplesToEat = amount; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetApplesToEat() { return ApplesToEat; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCoop(bool coop) { bIsCoop = coop; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetCoop() { return bIsCoop; };
};
