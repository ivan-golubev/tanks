// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankAimingComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();		
}

void ATank::AimAt(FVector target)
{
	TankAimingComponent->AimAt(target, ProjectileLaunchSpeed);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrel(UTankBarrel* barrelToSet)
{
	if (!barrelToSet) { return; }
	TankAimingComponent->SetBarrel(barrelToSet);
}

void ATank::SetTurret(UTankTurret* turretToSet)
{
	if (!turretToSet) { return; }
	TankAimingComponent->SetTurret(turretToSet);
}

