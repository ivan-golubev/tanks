// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto tank = GetControlledTank();
	if (!tank) { return; }
	
	int32 screenSizeX, screenSizeY;
	GetViewportSize(screenSizeX, screenSizeY);
	FVector2D screenLocation(screenSizeX*CrossHairXLocation, screenSizeY*CrossHairYLocation);	

	FVector tmp, lookDirection;
	DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, tmp, lookDirection);

	FVector rayStart = PlayerCameraManager->GetCameraLocation();	
	FVector rayEnd = rayStart + lookDirection * lineTraceRange;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetPawn());

	FHitResult outHitResult;
	GetWorld()->LineTraceSingleByChannel(
		outHitResult,
		rayStart,
		rayEnd,
		ECollisionChannel::ECC_Visibility,
		CollisionParams
	);	
	tank->AimAt(outHitResult.Location);	
}
