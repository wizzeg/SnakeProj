// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spawnable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Apple.generated.h"

UCLASS()
class SNAKEPROJ_API AApple : public ASpawnable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RootSceneComponent", meta = (AllowPrivateAccess = "true"));
	USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apple", meta = (AllowPrivateAccess = "true"));
	bool bEaten = false;
	
public:	
	// Sets default values for this actor's properties
	AApple();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Apple")
	bool EatApple(int32 playerID);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayParticleEffect();
};
