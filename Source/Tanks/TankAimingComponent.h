// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel;
class UTankTurret;

// Holds barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	void MoveBarrel(const FVector& AimDirection);
	void MoveTurret(const FVector& AimDirection);
	float To360Degrees(float YawRotation);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:			
	void AimAt(const FVector& hitLocation, float launchSpeed);
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrel(UTankBarrel*);	
	void SetTurret(UTankTurret*);
	UTankBarrel* GetBarrel();
	
};
