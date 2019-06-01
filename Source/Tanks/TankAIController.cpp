// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Tank.h"
#include "TankAIController.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	auto playerTank = GetWorld()->GetFirstPlayerController();
	auto controlledAITank = GetPawn();
	if (!ensure(playerTank && controlledAITank)) { return; }
	UTankAimingComponent* aiAimingComponent = controlledAITank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aiAimingComponent)) { return; }

	MoveToActor(playerTank, AcceptanceRadius);
	aiAimingComponent->AimAt(playerTank->GetPawn()->GetActorLocation());
	// Uncomment to let the AI tanks attack the player
	aiAimingComponent->Fire();
}


