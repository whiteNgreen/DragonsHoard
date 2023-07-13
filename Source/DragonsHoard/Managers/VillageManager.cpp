// Fill out your copyright notice in the Description page of Project Settings.


#include "VillageManager.h"
#include "../Enemies/RaidParty.h"
#include "../Enemies/VillagePath.h"

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
	
	TimerManager.SetTimer(TH_RaidSpawn, this, &AVillageManager::SpawnRaidParty, SpawnInterval, true);
}

// Called every frame
void AVillageManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimerManager.Tick(DeltaTime);
}

void AVillageManager::SpawnRaidParty()
{
	ARaidParty* RaidParty = Cast<ARaidParty>(GetWorld()->SpawnActor<AActor>(raidpartyclass, FTransform(FRotator(), villages[0]->GetActorLocation(), FVector(1))));
	if (RaidParty)
	{
		RaidParty->StartMovement(((AVillagePath*)villagePaths[0])->PathSpline);
	}
}

