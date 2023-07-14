// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAvatarAIController.generated.h"

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

protected:
	//UPROPERTY(BlueprintReadWrite, Category = "Movement")
		//FVector OrderedMovementLocation;
};
