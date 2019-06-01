// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class AProjectile;

UCLASS()
class TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector);
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UFUNCTION(BlueprintCallable)
	void Fire();	

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileLaunchSpeed = 4000.0f; // 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;
	
	double LastFireTime = 0.0f;

private:
	// Sets default values for this pawn's properties
	ATank();
	virtual void BeginPlay();
	UTankAimingComponent* TankAimingComponent;
};
