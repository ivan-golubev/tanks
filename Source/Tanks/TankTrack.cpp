// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float throttle)
{
	if (throttle != 0.0f)
	{
		auto ForceApplied = GetForwardVector() * throttle * TrackMaxDrivingForce;
		UE_LOG(LogTemp, Warning, TEXT("Applying force %s to location: %s"), *ForceApplied.ToString(), *GetComponentLocation().ToString())
		Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddForceAtLocation(
				ForceApplied,
				GetComponentLocation()
		);
	}
}

