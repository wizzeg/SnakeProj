// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldGenActor.generated.h"

constexpr ECollisionChannel Interactable_TC = ECC_GameTraceChannel1;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyWorld); // should be in gamestate

UCLASS()
class SNAKEPROJ_API AWorldGenActor : public AActor
{
	GENERATED_BODY()


private:
	UPROPERTY();
	TArray<AActor*> SpawnedActors;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MapSections");
	TSubclassOf<AActor> WallInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MapSections");
	TSubclassOf<AActor> FloorInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MapSections");
	TSubclassOf<AActor> AppleInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MapSections");
	TSubclassOf<AActor> LightInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenWorld");
	TArray<FVector> Spawns = { FVector::ZeroVector, FVector::ZeroVector };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenWorld");
	TArray<FVector> ApplePositions;

	// don't need this
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MapNumbers")
	//TArray<int32> IntArray;


public:	
	// Sets default values for this actor's properties
	AWorldGenActor();

	UPROPERTY(BlueprintAssignable, Category = "Events");
	FOnDestroyWorld OnDestroyWorld;

private:

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnActor(TSubclassOf<AActor> ActorType, FVector position);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "GenWorld")
	void GenerateMap(int32 num);

	UFUNCTION(BlueprintCallable, Category = "GenWorld")
	void DestroyMap();


	UFUNCTION(BlueprintCallable, Category = "GenWorld")
	FORCEINLINE TArray<FVector> GetSpawns() { return Spawns; };

	UFUNCTION(BlueprintCallable, Category = "GenWorld")
	FORCEINLINE TArray<FVector> GetApplePositions() { return ApplePositions; };

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	bool ValidAppleSpawn(FVector position);

	UFUNCTION(BlueprintCallable, Category = "WorldGen")
	void SpawnApple();

	UFUNCTION(BlueprintCallable, Category = "Event Launcher")
	FORCEINLINE void TriggerOnDestroyWorld() { OnDestroyWorld.Broadcast(); };
};
