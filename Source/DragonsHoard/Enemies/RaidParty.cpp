// Fill out your copyright notice in the Description page of Project Settings.


#include "RaidParty.h"
#include "VillagePath.h"
#include "../Managers/TimeManager.h"
#include "DebugMacros.h"

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
	
	TM_Simple_AddTick(this, &ARaidParty::MoveAlongSpline);
}

void ARaidParty::BeginDestroy()
{
	TM_Simple_RemoveTick(this, &ARaidParty::MoveAlongSpline);
	Super::BeginDestroy();
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

void ARaidParty::MoveAlongSpline_Implementation(float DeltaTime)
{
	PRINT("MOVING ALONG");
}

