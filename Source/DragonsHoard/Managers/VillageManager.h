// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VillageManager.generated.h"

/**
* Village manager handles 
*	Spawning of villages
*		Location
*		Path creation
*		Strength of the village
*	Spawning of raidpartys at each village
*	Village destruction
*/

UCLASS()
class DRAGONSHOARD_API AVillageManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVillageManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTimerManager TimerManager;

	// tmp method for spawning raidparties. Just for testing the GlobalTimeManager. -- TODO change to include buttons and stuff
	FTimerHandle TH_RaidSpawn;
	UPROPERTY(EditAnywhere)
		float SpawnInterval{ 2.f };
	UPROPERTY(EditAnywhere)
		TArray<AActor*> villages;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> villagePaths;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> raidpartyclass;
	UFUNCTION(BlueprintCallable)
		void SpawnRaidParty();
};
