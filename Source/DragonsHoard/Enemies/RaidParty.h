// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagAssetInterface.h"
#include "RaidParty.generated.h"

class USplineComponent;

UCLASS()
class DRAGONSHOARD_API ARaidParty : public AActor,
	public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARaidParty();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void BeginDestroy() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "GameplayTags")
		FGameplayTagContainer GameplayTags;
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const { TagContainer = GameplayTags; };



	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void StartMovement(USplineComponent* path);
	void StartMovement_Implementation(USplineComponent* path);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void MoveAlongSpline(float DeltaTime);
	void MoveAlongSpline_Implementation(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USplineComponent* Path{ nullptr };

};
