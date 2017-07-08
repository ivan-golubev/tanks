// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;

UCLASS()
class TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel* b);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurret(UTankTurret* b);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileLaunchSpeed = 100000.0f; // 1000 m/s
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;		
	
};
