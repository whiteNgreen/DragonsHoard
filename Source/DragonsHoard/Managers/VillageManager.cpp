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
	SpawnVillage();
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
	* 
	* TMP METOD: A timer delegate will spawn a new village when on is destroyed
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
	if (i >= VillagesAndPaths.Num()) {
		PRINTLONG(2.f, "Village not found");
		return;
	}
	
	if (DestroyedVillages.Enqueue(FDestroyedVillage(VillagesAndPaths[i], TimeToFinalVillageDestruction)))
	{
		FDestroyedVillage* VTD = DestroyedVillages.Peek();
		TimerManager.SetTimer(VTD->TH_ToFinalDestruction, [this]() {
				FDestroyedVillage* VTD = DestroyedVillages.Peek();
				AVillage* Village = VTD->VillageAndPath.Village;
				//PRINTARGLONG(2.f, "Final destruction of village: %s", *Village->GetName());
				Village->Destroy();
				
				DestroyedVillages.Pop();
			}, VTD->TimeToFinalDestruction, false);
	}

	VillagesAndPaths.RemoveAt(i);

	TimerManager.SetTimer(TH_VillageSpawn, this, &AVillageManager::SpawnVillage, 6.f);
}

void AVillageManager::SpawnVillage()
{
	/**
	* Spawning village should spawn both a village and a path
	*/
	FActorSpawnParameters params;
	FTransform transform(FRotator(0.0, -169.867181, 0.0), FVector(0, 1148.108454, 0.0), FVector(0.5f));
	AVillage* village = Cast<AVillage>(GetWorld()->SpawnActor<AActor>(VillageClass, transform, params));
	AVillagePath* path = Cast<AVillagePath>(GetWorld()->SpawnActor<AActor>(VillagePathClass, transform, params));
	if (!village || !path)
	{
		if (village)	village->Destroy();
		if (path)		path->Destroy();
		return;
	}

	FVillageAndPath vap;
	village->SetActorScale3D(transform.GetScale3D());
	path->SourceVillage = village;
	path->UpdatePath();	// Fører til BP error/warning når den aldri slettes, men oppdateres på ny village spawning
	vap.Village = village;
	vap.Path = path;
	VillagesAndPaths.Add(vap);
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

