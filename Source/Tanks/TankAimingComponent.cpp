// Fill out your copyright notice in the Description page of Project Settings.


#include "Tanks.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::MoveBarrel(const FVector& AimDirection)
{
	if (!barrel) { return; }
	// set Rotation.Pitch of the Barrel
	FRotator deltaRotator = AimDirection.Rotation() - barrel->GetForwardVector().Rotation();
	barrel->Elevate(deltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(const FVector& AimDirection)
{
	if (!turret) { return; }	
	// set Rotation.Yaw of the TurretMesh
	FRotator deltaRotator = AimDirection.Rotation() - turret->GetForwardVector().Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("Rotating the turret: %f"), deltaRotator.Yaw)
	float rotation = deltaRotator.Yaw;
	if (FMath::Abs<float>(rotation) > 180.0f)
	{
		rotation = 360.0f - FMath::Abs<float>(rotation);
		//UE_LOG(LogTemp, Warning, TEXT("Rotating the turret: %f"), rotation)
	}
	turret->Rotate(rotation);
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
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

void UTankAimingComponent::SetBarrel(UTankBarrel* barrelToSet) { barrel = barrelToSet; }
void UTankAimingComponent::SetTurret(UTankTurret* turretToSet) { turret = turretToSet; }

UTankBarrel* UTankAimingComponent::GetBarrel() { return barrel; }
