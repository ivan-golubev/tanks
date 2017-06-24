// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankAIController.h"
#include "TankPlayerController.h"

void ATankAIController::Tick(float deltaTime) 
{
	Super::Tick(deltaTime);
	AimToPlayerLocation();
}

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

void ATankAIController::AimToPlayerLocation() const
{
	ATank* playerTank = GetPlayerTank();
	ATank* controlledAITank = GetControlledTank();
	if (playerTank != nullptr && controlledAITank != nullptr)
	{
		controlledAITank->AimAt(playerTank->GetActorLocation());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI FAILED to aim the player's tank"))
	}
}


