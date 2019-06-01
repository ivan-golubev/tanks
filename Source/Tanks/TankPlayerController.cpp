// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto aimComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(aimComponent)) 
		OnAimingComponentInit(aimComponent);	
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto tankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(tankAimingComponent)) { return; }
	
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
	tankAimingComponent->AimAt(outHitResult.Location);
}
