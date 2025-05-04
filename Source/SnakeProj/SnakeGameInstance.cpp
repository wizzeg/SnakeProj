// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameInstance.h"

void USnakeGameInstance::AddSnakeControllers(TArray<ESnakeControllerType> types)
{
	for (int32 i = 0; i < types.Num(); i++)
	{
		ControllerTypes.Add(types[i]);
	}
}

void USnakeGameInstance::ClearSnakeControllers()
{
	ControllerTypes.Empty();
}

TArray<ESnakeControllerType> USnakeGameInstance::GetControllerTypes()
{
	return ControllerTypes;
}
