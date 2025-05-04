// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeSelector.h"


USnakeSelector::USnakeSelector(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bConstructed = true;
}


void USnakeSelector::IncreaseControllerType()
{
	controllerType = static_cast<ESnakeControllerType>(((static_cast<uint8>(controllerType) + CONTROLLERTYPECOUNT) + 1) % CONTROLLERTYPECOUNT);
}

void USnakeSelector::DecreaseControllerType()
{
	controllerType = static_cast<ESnakeControllerType>(((static_cast<uint8>(controllerType) + CONTROLLERTYPECOUNT) - 1) % CONTROLLERTYPECOUNT);
}

void USnakeSelector::SetDefaultSnakeControllerType(ESnakeControllerType type)
{
    if (bConstructed) return;
    controllerType = type;
}

FString USnakeSelector::GetControllerTypeName(ESnakeControllerType type)
{
    switch (type)
    {
    case ESnakeControllerType::HUMAN:
        return TEXT("Human");
    case ESnakeControllerType::AI:
        return TEXT("AI");
    case ESnakeControllerType::NONE:
        return TEXT("None");
    default:
        return TEXT("Unknown");
    }
}
