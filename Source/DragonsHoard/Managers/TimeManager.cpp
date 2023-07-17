// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"

// Sets default values
ATimeManager::ATimeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeManager::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ATimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DelegateTick(DeltaTime);
}

void ATimeManager::DelegateTick(float DeltaTime)
{
	switch (TimeTickType)
	{
	case ETimeTick::Pause:
		break;
	case ETimeTick::Tick:
		TimeTickDelegate.Broadcast(DeltaTime);
		break;
	case ETimeTick::AlwaysTick:
		TimeTickDelegate.Broadcast(DeltaTime);
		break;
	default:
		break;
	}
}

bool ATimeManager::TrySetTimeTick_Implementation(ETimeTick timetick)
{
	if (TimeTickType == ETimeTick::AlwaysTick && timetick == ETimeTick::LeaveAlwaysTick)
	{
		// Leave the AlwaysTick state and the correct next state 
		//	-- TODO: Change the next state based on the incomming LeaveAlwaysTick as it can require the next state to be Paused or Tick
		TimeTickType = ETimeTick::Tick;
		return true;
	}

	if (TimeTickType == timetick)
		return false;
	TimeTickType = timetick;
	return true;
}

