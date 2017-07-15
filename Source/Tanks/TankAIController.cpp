// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Tank.h"
#include "TankAIController.h"
#include "TankPlayerController.h"

void ATankAIController::Tick(float deltaTime) 
{
	Super::Tick(deltaTime);
	AimToPlayerLocation();
}

void ATankAIController::AimToPlayerLocation() const
{
	ATank* playerTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();
	ATank* controlledAITank = Cast<ATank>(GetPawn());
	if (playerTank && controlledAITank)
	{
		controlledAITank->AimAt(playerTank->GetActorLocation());
		controlledAITank->Fire();
	}
}


