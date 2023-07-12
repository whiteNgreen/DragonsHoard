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

	UFUNCTION(BlueprintCallable)
		void MoveOrder(FVector Location);

protected:
	//UPROPERTY(BlueprintReadWrite, Category = "Movement")
		//FVector OrderedMovementLocation;
};
