// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnManager.generated.h"

UCLASS()
class SNAKEPROJ_API APawnManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnManager();


	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Camera")
	FVector FindCameraPosition();

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void MoveCamera(FVector position);

	UFUNCTION(BlueprintCallable, Category = "Pawns")
	int32 AddPlayerPawn(APawn* pawn);

	UFUNCTION(BlueprintCallable, Category = "Pawns")
	int32 AddAIPawn(APawn* pawn);

	UFUNCTION(BlueprintCallable, Category = "Pawns")
	FORCEINLINE void ClearPlayerPawns() { PlayerPawns.Empty(); }

	UFUNCTION(BlueprintCallable, Category = "Player1")
	void MovePlayer1(ESnakeMoveDirection direction);

	UFUNCTION(BlueprintCallable, Category = "Player1")
	void MovePlayer2(ESnakeMoveDirection direction);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawns");
	TArray<APawn*> PlayerPawns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawns");
	TArray<APawn*> AIPawns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* RootSceneComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp;

public:
	UFUNCTION(BlueprintCallable, Category = "Event")
	void OnDestroyMap();
};
