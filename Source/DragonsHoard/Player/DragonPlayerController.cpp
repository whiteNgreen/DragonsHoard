// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonPlayerController.h"
#include "DebugMacros.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "../Managers/TimeManager.h"

void ADragonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(DefaultMappingContext, 0);
	}

	TM_GetTimerManager(this, TimerManager);
}

void ADragonPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (auto p = Cast<APlayerPawn>(InPawn)) {
		ControllerPawn = p;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s PlayerController failed cast to correct possessed pawn class %s"), *GetName(), __FUNCTION__);
	}
}

void ADragonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if (!IA_WorldClickAction)
		{
			UE_LOG(LogTemp, Error, TEXT("Missing UEnhancedInputAction on player controller. "));
			return;
		}

		EIC->BindAction(IA_WorldClickAction, ETriggerEvent::Triggered, this, &ADragonPlayerController::ClickAction);
		EIC->BindAction(IA_WorldClickAction, ETriggerEvent::Completed, this, &ADragonPlayerController::UnclickAction);

		EIC->BindAction(IA_WorldMovement, ETriggerEvent::Triggered, this, &ADragonPlayerController::WorldMove);
		EIC->BindAction(IA_WorldMovement, ETriggerEvent::Completed, this, &ADragonPlayerController::WorldMove);
	}
}

void ADragonPlayerController::ClickAction_Implementation()
{
	
}

void ADragonPlayerController::UnclickAction_Implementation()
{
}

void ADragonPlayerController::WorldMove(const FInputActionValue& Value)
{
	const FVector MovementVector = Value.Get<FVector>();
	ControllerPawn->WorldMove(MovementVector);
}

void ADragonPlayerController::EndWorldMove()
{
}
