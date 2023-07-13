// Fill out your copyright notice in the Description page of Project Settings.


#include "RaidParty.h"
#include "VillagePath.h"

// Sets default values
ARaidParty::ARaidParty()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARaidParty::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARaidParty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARaidParty::StartMovement_Implementation(USplineComponent* path)
{
	Path = path;
}

