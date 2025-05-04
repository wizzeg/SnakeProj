// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Spawnable.h"
#include "WorldGenActor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

UCLASS()
class SNAKEPROJ_API AWall : public ASpawnable
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<AWorldGenActor> SpawnerPtr;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta = (AllowPrivateAccess = "true"));
	USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* mesh;

public:
	// Sets default values for this actor's properties
	AWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
