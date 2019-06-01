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
	if (!ensure(LeftTrack && RightTrack))
		return;
	if (Throw != 0.0f) {
		//UE_LOG(LogTemp, Warning, TEXT("Intend Move Forward throw: %f"), Throw)
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::IntendRotateRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
		return;
	if (Throw != 0.0f) {
		//UE_LOG(LogTemp, Warning, TEXT("Intend Rotate right throw: %f"), Throw)
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto moveDirection = MoveVelocity.GetSafeNormal();
	auto moveForward = FVector::DotProduct(tankForward, moveDirection);

	auto crossZ = FVector::CrossProduct(tankForward, moveDirection).Z;
	IntendMoveForward(moveForward);
	IntendRotateRight(crossZ);
}

