// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldGenActor.h"
#include "Spawnable.h"


// Sets default values
AWorldGenActor::AWorldGenActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AWorldGenActor::SpawnActor(TSubclassOf<AActor> ActorType, FVector position)
{
    AActor* spawn = GetWorld()->SpawnActor<AActor>(ActorType, position, FRotator::ZeroRotator);
    ASpawnable* spawnable = Cast<ASpawnable>(spawn);
    if (spawnable)
    {
        spawnable->SubscribeToOnDestroyWorld(this);
    }
    SpawnedActors.Add(spawn);
}

// Called when the game starts or when spawned
void AWorldGenActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWorldGenActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldGenActor::GenerateMap(int32 num)
{
    float multiplier = 100.0f;
    if (WallInstance != nullptr && FloorInstance != nullptr)
    {
        FString FilePath = FPaths::ProjectContentDir() + TEXT("Maps/map") + FString::FromInt(num) + TEXT(".txt");
        FString FileContents;

        if (FFileHelper::LoadFileToString(FileContents, *FilePath))
        {
            TArray<FString> Lines;
            FileContents.ParseIntoArrayLines(Lines);
            for (size_t y = 0; y < Lines.Num(); y++)
            {
                for (size_t x = 0; x < Lines[y].Len(); x++)
                {
                    char type = Lines[y][x];
                    FVector position = FVector((Lines.Num() - y) * multiplier, x * multiplier, 0.0f);
                    if (type == '#')
                    {
                        SpawnActor(WallInstance, position);
                    }
                    else if (type == '.')
                    {
                        SpawnActor(FloorInstance, position);
                        ApplePositions.Add(position);
                    }
                    else if (type == '1')
                    {
                        if (!Spawns.IsValidIndex(0))
                        {
                            Spawns.Add(position);
                        }
                        Spawns[0] = position;
                        SpawnActor(FloorInstance, position);
                        ApplePositions.Add(position);
                    }
                    else if (type == '2')
                    {
                        while (!Spawns.IsValidIndex(1))
                        {
                            Spawns.Add(position);
                        }
                        Spawns[1] = position;
                        SpawnActor(FloorInstance, position);
                        ApplePositions.Add(position);
                    }
                }
            }

        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString("Failed generating string"));
        }
    }

}

void AWorldGenActor::DestroyMap()
{
    for (size_t i = 0; i < SpawnedActors.Num(); i++)
    {
        if (IsValid(SpawnedActors[i]))
        {
            SpawnedActors[i]->Destroy();
        }
    }
    SpawnedActors.Empty();
    Spawns.Empty();
    ApplePositions.Empty();
}

bool AWorldGenActor::ValidAppleSpawn(FVector position)
{
    TArray<FHitResult> HitResults;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    GetWorld()->SweepMultiByChannel(HitResults, position, position+FVector(0, 0,  50.0f), FQuat::Identity,
        Interactable_TC, FCollisionShape::MakeSphere(45.0f), QueryParams);
    bool bResult = true;
    for (const FHitResult& Hit : HitResults)
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, *HitActor->GetName());
            //UE_LOG(LogTemp, Warning, TEXT("Found object: %s"), *HitActor->GetName());
            bResult = false;
        }
    }
    return bResult;
}

void AWorldGenActor::SpawnApple()
{
	TArray<int32> indexes;
	indexes.Reserve(ApplePositions.Num());

	for (int32 i = 0; i < ApplePositions.Num(); i++)
	{
		indexes.Add(i);
	}
	int32 lastIndex = indexes.Num() - 1;

	for (size_t i = 0; i < indexes.Num(); i++)
	{
		int32 random = FMath::RandRange(0, lastIndex);
		if (ValidAppleSpawn(ApplePositions[indexes[random]]))
		{
			AActor* apple = GetWorld()->SpawnActor<AActor>(AppleInstance, ApplePositions[indexes[random]], FRotator::ZeroRotator);
            ASpawnable* spawnable = Cast<ASpawnable>(apple);
            if (spawnable)
            {
                spawnable->SubscribeOnDestroyMap();
                break;
            }
		}
		else
		{
			indexes[random] = indexes[lastIndex];
			lastIndex--;
		}
	}
}