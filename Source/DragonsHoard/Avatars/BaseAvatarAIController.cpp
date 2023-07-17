// Fill out your copyright notice in the Description page of Project 


#include "BaseAvatarAIController.h"
#include "DebugMacros.h"
#include "Kismet/GameplayStatics.h"
#include "../Managers/TimeManager.h"
#include "Navigation/PathFollowingComponent.h"

void ABaseAvatarAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TM_GetTimerManager(this, TimerManager);
}

void ABaseAvatarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EPathFollowingRequestResult::Type ABaseAvatarAIController::MoveOrder_Implementation(FVector Location)
{
	switch (AvatarAIState)
	{
	case EAvatarAIState::Idle:
		break;
	case EAvatarAIState::Moving:
		break;
	case EAvatarAIState::Sleeping:
		LeaveSleep();
		break;
	case EAvatarAIState::Attack:
		break;
	default:
		break;
	}
	AvatarAIState = EAvatarAIState::Moving;
	return MoveToLocation(Location);
}

void ABaseAvatarAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	AvatarAIState = EAvatarAIState::Idle;
	if (TimerManager)
	{
		TimerManager->TrySetTimeTick(ETimeTick::Pause);
	}
	if (!Result.IsInterrupted())
	{
		OnMoveCompletedDelegate.Broadcast();
		OnMoveCompletedDelegate.Clear();
	}
	// For not clearing the sleep delegate when movement is interrupted to move towards the Hoard
	if (MovementAssumption.AssumedNextState == EAvatarAIState::Sleeping &&
		MovementAssumption.StateAtAssumption == EAvatarAIState::Moving) 
		OnMoveCompletedDelegate.Clear();
}

void ABaseAvatarAIController::AssumeNextState_Implementation(EAvatarAIState assumedState)
{
	MovementAssumption = FMovementAssumption(assumedState, AvatarAIState);
}

void ABaseAvatarAIController::EnterSleep_Implementation()
{
	//TM_AddTickDelegate(TimerManager, this, &ABaseAvatarAIController::TickSleep);
	AvatarAIState = EAvatarAIState::Sleeping;
	AssumeNextState(EAvatarAIState::Moving);
}

void ABaseAvatarAIController::TickSleep_Implementation(float DeltaTime)
{
}

void ABaseAvatarAIController::LeaveSleep_Implementation()
{
	//TM_RemoveTickDelegate(TimerManager, this, &ABaseAvatarAIController::TickSleep);
}

