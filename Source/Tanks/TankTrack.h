// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float throttle);
	
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 88880.0f * 500.0f; // DrivingForce [N] = mass [kg] * acceleration [m/s^2]
	//  = 40,000 kg * 2.222 m/s^2 = 88880
	// acceleration: http://www.wolframalpha.com/input/?i=0+to+80+km+per+hour+in+10+seconds
	// additionally, since it's a game, let's multiply it by 500 )))))) LOL
};
