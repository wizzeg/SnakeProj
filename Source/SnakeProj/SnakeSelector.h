// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SnakeSelector.generated.h"
#define CONTROLLERTYPECOUNT 3

UENUM(BlueprintType)
enum class ESnakeControllerType : uint8
{
	HUMAN,
	AI,
	NONE
};
/**
 * 
 */
UCLASS()
class SNAKEPROJ_API USnakeSelector : public UUserWidget
{
	GENERATED_BODY()
	
private:
	bool bConstructed = false;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "", meta = (AllowPrivateAcces = "true"));
	ESnakeControllerType controllerType = ESnakeControllerType::HUMAN;
protected:
	UFUNCTION(BlueprintCallable)
	void IncreaseControllerType();
	UFUNCTION(BlueprintCallable)
	void DecreaseControllerType();
	UFUNCTION(BlueprintCallable)
	void SetDefaultSnakeControllerType(ESnakeControllerType type);

public:
	USnakeSelector(const FObjectInitializer& ObjectInitializer);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ESnakeControllerType GetContollerType() { return controllerType; };
	UFUNCTION(BlueprintCallable)
	static FString GetControllerTypeName(ESnakeControllerType type);
};
