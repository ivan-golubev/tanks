// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Tank.h"
#include "TankAIController.h"
#include "TankPlayerController.h"

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	ATank* playerTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();
	ATank* controlledAITank = Cast<ATank>(GetPawn());
	if (playerTank && controlledAITank)
	{
		MoveToActor(playerTank, AcceptanceRadius);

		controlledAITank->AimAt(playerTank->GetActorLocation());
		// Uncomment to let the AI tanks attack the player
		controlledAITank->Fire();
	}
}


