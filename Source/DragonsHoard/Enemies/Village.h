// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Village.generated.h"

UCLASS()
class DRAGONSHOARD_API AVillage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVillage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
