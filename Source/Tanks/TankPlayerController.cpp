// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	ATank* actor = GetControlledTank();
	if (actor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessing the tank %s"), *actor->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No tank attached"))
	}	
}

