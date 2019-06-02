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

class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
	bool isBarrelMoving;

	void MoveBarrel(const FVector& AimDirection);
	void MoveTurret(const FVector& AimDirection);	
	float To360Degrees(float YawRotation);

protected:	
	UTankAimingComponent();
	void BeginPlay();
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringStatus firingStatus = EFiringStatus::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileLaunchSpeed = 4000.0f; // 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	double LastFireTime = 0.0f;

public:		
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Init(UTankBarrel* barrel, UTankTurret* turret);
	void AimAt(const FVector& hitLocation);
	
	UFUNCTION(BlueprintCallable)
	void Fire();
	
};
