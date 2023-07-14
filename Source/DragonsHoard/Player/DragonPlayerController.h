// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "DragonPlayerController.generated.h"


class ATimeManager;
class APlayerPawn;
/**
 * 
 */
UCLASS()
class DRAGONSHOARD_API ADragonPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Player Input")
		void ClickAction();
	void ClickAction_Implementation();

	void WorldMove(const FInputActionValue& Value);
	void EndWorldMove();

	UPROPERTY(BlueprintReadWrite, Category = "Player Avatar")
		class ABaseAvatarAIController* PlayerAvatarController{ nullptr };


private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		APlayerPawn* ControllerPawn;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		ATimeManager* TimerManager{ nullptr };
	/**
	* Enhanced input mapping context and actions
	*/
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputMappingContext* DefaultMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputAction* IA_WorldClickAction{ nullptr };
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputAction* IA_WorldMovement{ nullptr };
};
