// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	/* movement speed in the range [-1, 1] */
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 5.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinBarrelElevation = 0.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxBarrelElevation = 20.0f;
};
