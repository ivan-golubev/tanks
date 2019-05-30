// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class TANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()	

protected:	
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void OnAimingComponentInit(UTankAimingComponent* aimComponent);
	void BeginPlay() override;
	void Tick(float) override;
		
private:	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float lineTraceRange = 1000000.0f; // 10 kilometers
	void AimTowardsCrosshair(); // rotate the barrel towards the crosshair

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;
};
