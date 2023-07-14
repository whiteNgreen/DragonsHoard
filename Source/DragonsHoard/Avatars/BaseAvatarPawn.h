// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagAssetInterface.h"
#include "BaseAvatarPawn.generated.h"

UCLASS()
class DRAGONSHOARD_API ABaseAvatarPawn : public ACharacter,
	public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseAvatarPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	FGameplayTagContainer GameplayTags;
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const { TagContainer = GameplayTags };
};
