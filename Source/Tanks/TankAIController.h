// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class TANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	void Tick(float) override;

	// Acceptance Radius = 30 meters - how close the AI tank can get to the player
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 3000.0f;

};
