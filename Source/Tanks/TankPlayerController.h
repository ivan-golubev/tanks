// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:	
	void BeginPlay() override;
	void Tick(float) override;

public:
	ATank* GetControlledTank() const;
		
private:	
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000.0f; // 10 kilometers

	void AimTowardsCrosshair(); // rotate the barrel towards the crosshair
};
