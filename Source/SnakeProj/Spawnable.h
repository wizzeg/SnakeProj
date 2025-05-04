// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawnable.generated.h"

UCLASS()
class SNAKEPROJ_API ASpawnable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnable();


protected:
	TWeakObjectPtr<class AWorldGenActor> SpawnerPtr;
	TWeakObjectPtr<class ASnakeGameStateBase> GameStateWPtr;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Life")
	FORCEINLINE void DestroySelf() { Destroy(); };


	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Bind")
	virtual void SubscribeToOnDestroyWorld(class AWorldGenActor* WorldGenerator); // This thing would've benefited from a base class or interface (like "Spawnable"), but I'm not making one now
	


	UFUNCTION(BlueprintCallable, Category = "Bind")
	virtual void SubscribeOnDestroyMap(); // This thing would've benefited from a base class or interface (like "Spawnable"), but I'm not making one now
};
