// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	ATank* actor = GetControlledTank();
	if (actor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Possessing the tank %s"), *actor->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI No tank attached"))
	}
}


