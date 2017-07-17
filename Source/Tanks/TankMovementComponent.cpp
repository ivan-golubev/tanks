// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Init(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{ 
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (LeftTrack && RightTrack && Throw != 0.0f) {
		//UE_LOG(LogTemp, Warning, TEXT("Intend Move Forward throw: %f"), Throw)
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::IntendRotateRight(float Throw)
{
	if (LeftTrack && RightTrack && Throw != 0.0f) {
		//UE_LOG(LogTemp, Warning, TEXT("Intend Rotate right throw: %f"), Throw)
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
	}
}

