// Fill out your copyright notice in the Description page of Project Settings.


#include "Tanks.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

void UTankAimingComponent::MoveBarrel(const FVector& AimDirection)
{
	if (!barrel) { return; }
	// set Rotation.Pitch of the Barrel
	FRotator deltaRotator = AimDirection.Rotation() - barrel->GetForwardVector().Rotation();
	barrel->Elevate(deltaRotator.Pitch);
}

float UTankAimingComponent::To360Degrees(float rot) { return rot > 0 ? rot : rot + 360.0f; }

void UTankAimingComponent::MoveTurret(const FVector& AimDirection)
{
	if (!turret) { return; }	
	float aimRotation = To360Degrees(AimDirection.Rotation().Yaw);
	float currentTurretRotation = To360Degrees(turret->GetForwardVector().Rotation().Yaw);

	float relativeRotation = aimRotation - currentTurretRotation;
	/* calculate the opposite rotation: */
	float oppositeRelativeRotation = (360.0f - FMath::Abs<float>(relativeRotation)) * FMath::Sign(relativeRotation) * (-1);
	/* rotate the turret using the shortest path */
	turret->Rotate(
		FMath::Abs<float>(relativeRotation) < FMath::Abs<float>(oppositeRelativeRotation)
		? relativeRotation
		: oppositeRelativeRotation
	);
}

void UTankAimingComponent::Init(UTankBarrel* b, UTankTurret* t)
{
	PrimaryComponentTick.bCanEverTick = false;
	this->barrel = b;
	this->turret = t;
}

void UTankAimingComponent::AimAt(const FVector& hitLocation, float launchSpeed)
{
	if (!barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = barrel->GetSocketLocation(FName("ProjectileSocket"));

	bool haveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		hitLocation,
		launchSpeed,
		false,
		.0f,
		.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (haveAimSolution) 
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetOwner()->GetName(), *AimDirection.ToString())
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("%s No aiming solution"), *GetOwner()->GetName())
	//}
}

UTankBarrel* UTankAimingComponent::GetBarrel() { return barrel; }
