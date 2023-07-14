// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TimeManager.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimeTickDelegate)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimeTickDelegate, float, DeltaTime);

UENUM(BlueprintType)
enum class ETimeTick : uint8
{
	Pause,
	Tick
};


#define TM_GetTimerManager(Object, TimerManager) 	\
	AActor* tm = UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass());			\
		if (tm)																							\
			TimerManager = Cast<ATimeManager>(tm);														\
		else																							\
			UE_LOG(LogTemp, Error, TEXT("%s. failed to get TimerManager of class %s"), *Object->GetName(), *ATimeManager::StaticClass()->GetDefaultObject()->GetName())	

#define TM_AddTickDelegate(TimerManager, Object, Func)	\
		if (TimerManager)								\
			TimerManager->TimeTickDelegate.AddDynamic(Object, Func)

#define TM_RemoveTickDelegate(TimerManager, Object, Func)	\
		if (TimerManager)								\
			TimerManager->TimeTickDelegate.RemoveDynamic(Object, Func)

#define TM_Simple_AddTick(Object, Func)	\
		ATimeManager* t = nullptr;		\
		TM_GetTimerManager(Object, t);	\
		TM_AddTickDelegate(t, Object, Func);

#define TM_Simple_RemoveTick(Object, Func)	\
		ATimeManager* t = nullptr;			\
		TM_GetTimerManager(Object, t);		\
		TM_RemoveTickDelegate(t, Object, Func);


UCLASS()
class DRAGONSHOARD_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DelegateTick(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool TrySetTimeTick(ETimeTick timetick);
	bool TrySetTimeTick_Implementation(ETimeTick timetick);

	UPROPERTY(BlueprintReadWrite, Category = "TimeTick")
		ETimeTick TimeTickType;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, Category = "TimeTick")
		FTimeTickDelegate TimeTickDelegate;
};
