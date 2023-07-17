// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "GameplayTagAssetInterface.h"
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

class AVillage;
class AVillagePath;

USTRUCT(BlueprintType)
struct FVillageAndPath
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AVillage* Village{ nullptr };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AVillagePath* Path{ nullptr };
};

USTRUCT(BlueprintType)
struct FDestroyedVillage
{
	GENERATED_BODY()
public:
	FDestroyedVillage(){}
	FDestroyedVillage(const FVillageAndPath village, float timetofinaldestruction)
		: DestroyedVillage(village), TimeToFinalDestruction(timetofinaldestruction)
	{}
	UPROPERTY(BlueprintReadWrite)
		FVillageAndPath DestroyedVillage{ nullptr };
	UPROPERTY(BlueprintReadWrite)
		float TimeToFinalDestruction{ 10.f };
	UPROPERTY(BlueprintReadWrite)
		FTimerHandle TH_ToFinalDestruction;
};

UCLASS()
class DRAGONSHOARD_API AVillageManager : public AActor,
	public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVillageManager();

	UPROPERTY(BlueprintReadWrite, Category = "GameplayTags")
		FGameplayTagContainer GameplayTags;
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = GameplayTags; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void TimerTick(float DeltaTime);

	UFUNCTION(BlueprintCallable)
		void StartTimer(float time);
	FTimerManager TimerManager;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Village Destruction")
		void DestroyVillage(AVillage* VillageToDestroy);
	void DestroyVillage_Implementation(AVillage* VillageToDestroy);


	// tmp method for spawning raidparties. Just for testing the GlobalTimeManager. -- TODO change to include buttons and stuff to spawn villages randomly in runtime
	UPROPERTY(BlueprintReadWrite, Category = "TimeTick")
		FTimerHandle TH_RaidSpawn;
	UPROPERTY(EditAnywhere)
		float SpawnInterval{ 2.f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Village Destruction")
		float TimeToFinalVillageDestruction{ 10.f };
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FVillageAndPath> VillagesAndPaths;

	TQueue<FDestroyedVillage> DestroyedVillages;

	UPROPERTY(BlueprintReadOnly, Category = "Village Destruction")
		TArray<AVillagePath*> PathsMarkedForDestruction;
	//UPROPERTY(EditAnywhere)
	//	TArray<AActor*> villagePaths;
	

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> raidpartyclass;
	UFUNCTION(BlueprintCallable)
		void SpawnRaidParty();
};
