// Fill out your copyright notice in the Description page of Project 


#include "BaseAvatarAIController.h"
#include "DebugMacros.h"
#include "Kismet/GameplayStatics.h"
#include "../Managers/TimeManager.h"

void ABaseAvatarAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AActor* tm = UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass());
	if (tm)
		TimerManager = Cast<ATimeManager>(tm);
	else
		UE_LOG(LogTemp, Error, TEXT("%s. failed to get TimerManager of class %s"), *GetName(), *ATimeManager::StaticClass()->GetDefaultObject()->GetName());

}

void ABaseAvatarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EPathFollowingRequestResult::Type ABaseAvatarAIController::MoveOrder_Implementation(FVector Location)
{
	return MoveToLocation(Location);
}

void ABaseAvatarAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (TimerManager)
	{
		TimerManager->TrySetTimeTick(ETimeTick::Pause);
	}
}
