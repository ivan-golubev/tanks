// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankPlayerController.h"

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

	FHitResult outHitResult;
	GetWorld()->LineTraceSingleByChannel(outHitResult, rayStart, rayEnd, ECollisionChannel::ECC_PhysicsBody);	
	tank->AimAt(outHitResult.Location);	
	//if (outHitResult.GetActor())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Hit object %s"), *outHitResult.GetActor()->GetName())
	//}
}
