// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEPROJ_API ASnakeGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable")
	TSubclassOf<class ASnakePawn> SnakePawnClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable")
	TSubclassOf<class ASnakeAIController> SnakeAIControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable")
	TSubclassOf<class AWorldGenActor> WorldGenClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	int32 CurrentMapNum = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	bool bAIControllersCreated = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldGen")
	class AActor* WorldGenerator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllers")
	TArray<class AAIController*> AIControllers;


protected:
	UFUNCTION(BlueprintCallable, Category = "Initialize")
	void CreateSnakes(TArray<ESnakeControllerType> types, TArray<FVector> positions);

	UFUNCTION(BlueprintCallable, Category = "WorldGen")
	void NextMap(int32 mapNum);

	UFUNCTION(BlueprintCallable, Category = "WorldGen")
	void SpawnMapGenActor();

	UFUNCTION(BlueprintCallable, Category = "WorldGen")
	FORCEINLINE class AActor* GetWorldGenerator() { return WorldGenerator; };

	UFUNCTION(BlueprintCallable, Category = "Event")
	void AppleEaten(int32 playerID);


public:
	UFUNCTION(BlueprintCallable, Category = "Event")
	void OnDestroyMap();

	UFUNCTION(BlueprintNativeEvent, Category = "Event")
	void NoMoreMaps();
};