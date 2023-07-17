// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VillagePath.generated.h"

class USplineComponent;

UCLASS()
class DRAGONSHOARD_API AVillagePath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVillagePath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USplineComponent* PathSpline;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Destruction")
		void DestroyPath();
	void DestroyPath_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Editor Function")
		void UpdatePath();
	void UpdatePath_Implementation();

};
