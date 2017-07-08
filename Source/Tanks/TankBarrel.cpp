// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	/* make sure the elevation stays within the min-max range */
	auto NewElevation = FMath::Clamp<float>(RelativeRotation.Pitch + ElevationChange, MinBarrelElevation, MaxBarrelElevation);	
	SetRelativeRotation(FRotator(NewElevation, .0f, .0f));
}

