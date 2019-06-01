// Fill out your copyright notice in the Description page of Project Settings.


#include "Tanks.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Projectile.h"

void UTankAimingComponent::MoveBarrel(const FVector& AimDirection)
{
	if (!ensure(barrel)) { return; }
	// set Rotation.Pitch of the Barrel
	FRotator deltaRotator = AimDirection.Rotation() - barrel->GetForwardVector().Rotation();
	barrel->Elevate(deltaRotator.Pitch);
}

float UTankAimingComponent::To360Degrees(float rot) { return rot > 0 ? rot : rot + 360.0f; }

void UTankAimingComponent::MoveTurret(const FVector& AimDirection)
{
	if (!ensure(turret)) { return; }	
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

void UTankAimingComponent::AimAt(const FVector& hitLocation)
{
	if (!ensure(barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = barrel->GetSocketLocation(FName("ProjectileSocket"));

	bool haveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		hitLocation,
		ProjectileLaunchSpeed,
		false,
		.0f,
		.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (haveAimSolution) 
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{	
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isReloaded)
	{
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			barrel->GetSocketLocation(FName("ProjectileSocket")),
			barrel->GetSocketRotation(FName("ProjectileSocket"))
			);
		projectile->LaunchProjectile(ProjectileLaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
