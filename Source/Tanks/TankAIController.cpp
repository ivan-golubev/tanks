// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankAIController.h"
#include "TankPlayerController.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc != nullptr)
	{
		return Cast<ATankPlayerController>(pc)->GetControlledTank();
	}
	return nullptr;
}

void ATankAIController::BeginPlay()
{
	ATank* actor = GetPlayerTank();
	if (actor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI has found player's tank %s"), *actor->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI FAILED to find the player's tank"))
	}
}


