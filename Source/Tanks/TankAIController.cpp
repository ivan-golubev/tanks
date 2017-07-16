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
		// TODO: uncomment this to aim at player
		//controlledAITank->AimAt(playerTank->GetActorLocation());
		// TODO: uncomment this to allow AI attacking the player
		//controlledAITank->Fire();
	}
}


