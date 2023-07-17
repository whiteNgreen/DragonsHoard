// Fill out your copyright notice in the Description page of Project Settings.


#include "VillagePath.h"
#include "Components/SplineComponent.h"

// Sets default values
AVillagePath::AVillagePath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PathSpline = CreateDefaultSubobject<USplineComponent>("PathSpline");
	PathSpline->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AVillagePath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVillagePath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVillagePath::DestroyPath_Implementation()
{
	// Kinda sketchy, as Raidparties mights still be referencing this object. But destroying pathways should probably be done by the manager
	SetLifeSpan(20.f);
}

void AVillagePath::UpdatePath_Implementation()
{
}

