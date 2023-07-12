#pragma once
#include "CoreMinimal.h"

/**
* Containing debug print macros for easy use
* Also has a class meant for measuring time for code optimizations
*/

#define DEBUG !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
#ifdef DEBUG

// Print To Screen MACROS

	// Print text
	#define PRINT(X)				( GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT(X))) )
	#define PRINTLONG(T, X)			( GEngine->AddOnScreenDebugMessage(-1, T,	FColor::Blue, FString::Printf(TEXT(X))) )

	// Print text that accepts arguments
	#define PRINTARG(X, ...)		( GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, FString::Printf(TEXT(X), ##__VA_ARGS__)) )
	#define PRINTARGLONG(T, X, ...)	( GEngine->AddOnScreenDebugMessage(-1, T, FColor::Yellow, FString::Printf(TEXT(X), ##__VA_ARGS__)) )

// Draw visual debug aid

	// Draws debug line from actor location
	#define ADRAWLINE(Vec, Color, T) ( DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + (Vec), Color, false, T, 0, 5.f) )

	// Draws debug line from actor location
	#define AADRAWLINE(Vec, Actor, Color, T) ( DrawDebugLine(GetWorld(), Actor->GetActorLocation(), Actor->GetActorLocation() + (Vec), Color, false, T, 0, 5.f) )


	// Draws line from Start to End
	#define DRAWLINE(Start, End, Color, T) ( DrawDebugLine(GetWorld(), Start, End, Color, false, T, 0, 5.f) )

	// Draws point at Vec
	#define DRAWPOINT(Vec, Color, T) ( DrawDebugPoint(GetWorld(), Vec, 20.f, Color, false, T, 0) )


// Timer Class
	#include <chrono>

	class TIMER
	{
	public:
		static enum class TimeType : uint32
		{
			NANO	= 1,
			MICRO	= (uint32)1e3,
			MILLI	= (uint32)1e6,
			SECOND	= (uint32)1e9
		};

		TIMER(bool ImmediateStart = true)
		{
			if (ImmediateStart){
				time = TimeNow();
			}
		}
		~TIMER() {}
		void StartTimer()
		{
			time = TimeNow();
		}

		void PrintTime(float TimeToDisplay = 0.f, FString Message = "", TimeType type = TimeType::MILLI)
		{
			FString st;
			switch (type)
			{
			case TIMER::TimeType::NANO:		st = "Nanoseconds";				break;
			case TIMER::TimeType::MICRO:	st = "Microseconds";			break;
			case TIMER::TimeType::MILLI:	st = "Milliseconds";			break;
			case TIMER::TimeType::SECOND:	st = "Seconds";					break;
			default:														break;
			}
			Message += FString::Printf(TEXT(" = %f %s"), GetTimepoint((double)type), *st);
			GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, FColor::Yellow, Message);
		}
	private:
		typedef std::chrono::high_resolution_clock::time_point Timepoint;
		Timepoint time;

		FORCEINLINE Timepoint TimeNow() { return std::chrono::high_resolution_clock::now(); }
		FORCEINLINE float GetTimepoint(double type) { return (float)(Duration(TimeNow() - time) / (type)); }
		FORCEINLINE long long Duration(std::chrono::duration<long long, std::nano> t) { return std::chrono::duration_cast<std::chrono::nanoseconds>(t).count(); }
	};

#endif // DEBUG
