// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAvatarAIController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveCompleted);

UENUM(BlueprintType)
enum class EAvatarAIState : uint8
{
	Idle,
	Moving,
	Sleeping,
	Attack
};

USTRUCT(BlueprintType)
struct FMovementAssumption
{
	GENERATED_BODY()
public:
	FMovementAssumption(){}
	FMovementAssumption(EAvatarAIState assumption, EAvatarAIState current)
		:AssumedNextState(assumption), StateAtAssumption(current)
	{}
	UPROPERTY(BlueprintReadWrite)
		EAvatarAIState AssumedNextState;	
	UPROPERTY(BlueprintReadWrite)
		EAvatarAIState StateAtAssumption;
};

/**
 * 
 */
UCLASS()
class DRAGONSHOARD_API ABaseAvatarAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		EPathFollowingRequestResult::Type MoveOrder(FVector Location);
	virtual EPathFollowingRequestResult::Type MoveOrder_Implementation(FVector Location);

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeTick")
		class ATimeManager* TimerManager{ nullptr };

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
		FOnMoveCompleted OnMoveCompletedDelegate;

public:	// State functions
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "States")
	//	bool EnterState(EAvatarAIState newState);
	//bool EnterState_Implementation(EAvatarAIState newState);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "States")
		void AssumeNextState(EAvatarAIState assumedState);
	void AssumeNextState_Implementation(EAvatarAIState assumedState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Sleep")
		void EnterSleep();
	void EnterSleep_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Sleep")
		void TickSleep(float DeltaTime);
	void TickSleep_Implementation(float DeltaTime);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Sleep")
		void LeaveSleep();
	void LeaveSleep_Implementation();

public:	// State variables
	UPROPERTY(BlueprintReadWrite, Category = "States")
		EAvatarAIState AvatarAIState;
	UPROPERTY(BlueprintReadWrite, Category = "States")
		FMovementAssumption MovementAssumption;
};
