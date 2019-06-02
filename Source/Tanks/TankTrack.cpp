// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = false;
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTank();
	ApplySidewaysForce();
	Throttle = 0.0f;
}

void UTankTrack::ApplySidewaysForce()
{
	auto right = GetRightVector();
	auto slippageSpeed = FVector::DotProduct(GetComponentVelocity(), right);
	auto correctionAcceleration = -slippageSpeed / GetWorld()->GetDeltaSeconds() * right;

	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = correctionAcceleration * tankRoot->GetMass() / 2;
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float throttle)
{
	Throttle = FMath::Clamp<float>(Throttle+throttle, -1.0f, 1.0f);
}

void UTankTrack::DriveTank() 
{
	if (Throttle != 0.0f)
	{
		auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
		//UE_LOG(LogTemp, Warning, TEXT("Applying force %s to location: %s"), *ForceApplied.ToString(), *GetComponentLocation().ToString())
		Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddForceAtLocation(
			ForceApplied,
			GetComponentLocation()
		);
	}
}

