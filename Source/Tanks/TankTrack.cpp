// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s throttling: %f"), *GetName(), throttle)
	auto ForceApplied = GetForwardVector() * throttle * TrackMaxDrivingForce;
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddForceAtLocation(
		ForceApplied, 
		GetComponentLocation()
	);
}

