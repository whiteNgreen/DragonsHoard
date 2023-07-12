// Fill out your copyright notice in the Description page of Project 


#include "BaseAvatarAIController.h"
#include "DebugMacros.h"

void ABaseAvatarAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABaseAvatarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseAvatarAIController::MoveOrder(FVector Location)
{
	MoveToLocation(Location);
}
