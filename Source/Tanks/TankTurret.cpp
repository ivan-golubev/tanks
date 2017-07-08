// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	//RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	RotationChange = FMath::Clamp<float>(RotationChange, -360.0f, 360.0f);
	UE_LOG(LogTemp, Warning, TEXT("RotationChange: %f"), RotationChange)
	SetRelativeRotation(FRotator(.0f, RotationChange, .0f));	
}


