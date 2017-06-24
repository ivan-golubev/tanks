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

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	UE_LOG(LogTemp, Warning, TEXT("Screen location is %s"), *screenLocation.ToString())

	FVector rayStart, rayEnd;
	GetRayCastParams(rayStart, rayEnd);

	FHitResult outHitResult;
	GetWorld()->LineTraceSingleByChannel(outHitResult, rayStart, rayEnd, ECollisionChannel::ECC_Destructible);
	if (outHitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit object %s"), *outHitResult.GetActor()->GetName())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Nothing"))
	}
}

void ATankPlayerController::GetRayCastParams(FVector& outStart, FVector& outEnd) const
{
	FRotator playerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(outStart, playerRotation);
	outEnd = outStart + playerRotation.Vector() * ATank::TANK_SHOOT_DISTANCE;
}
