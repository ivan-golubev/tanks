// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM(BlueprintType)
enum class EFiringStatus: uint8
{
	Reloading,
	Aiming,
	Locked
};

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
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringStatus firingStatus = EFiringStatus::Aiming;

public:		
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Init(UTankBarrel* barrel, UTankTurret* turret);
	void AimAt(const FVector& hitLocation, float launchSpeed);
	UTankBarrel* GetBarrel();
};
