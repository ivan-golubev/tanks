// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//UE_LOG(LogTemp, Display, TEXT("ATank::ATank()"))
}

void ATank::BeginPlay() 
{	
	Super::BeginPlay();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	//UE_LOG(LogTemp, Display, TEXT("ATank::BeginPlay()"))
}

void ATank::AimAt(FVector target)
{
	if (ensure(TankAimingComponent))
		TankAimingComponent->AimAt(target, ProjectileLaunchSpeed);
}

void ATank::Fire()
{
	if (!ensure(TankAimingComponent))
		return;
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	UTankBarrel* barrel = TankAimingComponent->GetBarrel();
	if (barrel && isReloaded) 
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

