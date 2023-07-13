// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RaidParty.generated.h"

class USplineComponent;

UCLASS()
class DRAGONSHOARD_API ARaidParty : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARaidParty();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void StartMovement(USplineComponent* path);
	void StartMovement_Implementation(USplineComponent* path);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USplineComponent* Path{ nullptr };

};
