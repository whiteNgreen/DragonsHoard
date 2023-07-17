// Fill out your copyright notice in the Description page of Project Settings.


#include "VillageManager.h"
#include "../Enemies/RaidParty.h"
#include "../Enemies/Village.h"
#include "../Enemies/VillagePath.h"
#include "TimeManager.h"
#include "DebugMacros.h"

// Sets default values
AVillageManager::AVillageManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVillageManager::BeginPlay()
{
	Super::BeginPlay();
	

	TM_Simple_AddTick(this, &AVillageManager::TimerTick);
}

// Called every frame
void AVillageManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVillageManager::TimerTick(float DeltaTime)
{
	TimerManager.Tick(DeltaTime);
}

void AVillageManager::StartTimer(float time)
{
	TimerManager.SetTimer(TH_RaidSpawn, this, &AVillageManager::SpawnRaidParty, time, true);
}

void AVillageManager::DestroyVillage_Implementation(AVillage* VillageToDestroy)
{
	/**
	* When a village is destroyed, the linked path will be marked for destruction. 
	* The struct containing the two will be moved over to a separate TArray to keep track of when they should be 
	*	finally destroyed and removed from memory
	*/
	if (VillagesAndPaths.Num() == 0) 
		return;

	int i{};
	for (const auto& vp : VillagesAndPaths) {
		if (vp.Village == VillageToDestroy) {
			PRINTARGLONG(2.f, "Destroying village: %s", *vp.Village->GetName());
			break;
		}
		i++;
	}
	
	if (DestroyedVillages.Enqueue(FDestroyedVillage(VillagesAndPaths[i], TimeToFinalVillageDestruction)))
	{
		FDestroyedVillage* VTD = DestroyedVillages.Peek();
		TimerManager.SetTimer(VTD->TH_ToFinalDestruction, [this]() {
				FDestroyedVillage* VTD = DestroyedVillages.Peek();
				AVillage* Village = VTD->DestroyedVillage.Village;
				PRINTARGLONG(2.f, "Final destruction of village: %s", *Village->GetName());
				Village->Destroy();
				
				DestroyedVillages.Pop();
			}, VTD->TimeToFinalDestruction, false);
	}

	VillagesAndPaths.RemoveAt(i);
}

void AVillageManager::SpawnRaidParty()
{
	if (VillagesAndPaths.Num() == 0) return;

	ARaidParty* RaidParty = Cast<ARaidParty>(GetWorld()->SpawnActor<AActor>(raidpartyclass, FTransform(FRotator(), VillagesAndPaths[0].Village->GetActorLocation(), FVector(1))));
	if (RaidParty)
	{
		RaidParty->StartMovement(((AVillagePath*)VillagesAndPaths[0].Path)->PathSpline);
	}
}

