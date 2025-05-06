// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"
#include "SnakeGameStateBase.h"

// Sets default values
AApple::AApple()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootSceneComponent;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	mesh->SetupAttachment(RootSceneComponent);

}



// Called when the game starts or when spawned
void AApple::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AApple::EatApple(int32 playerID)
{
	if (bEaten) return false;
	PlayParticleEffect();
	if (GameStateWPtr.IsValid())
	{
		GameStateWPtr->TriggerOnAppleEaten(playerID);
		DestroySelf();
		return true;
	}
	return false;
}

