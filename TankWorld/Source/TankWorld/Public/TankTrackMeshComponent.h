// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackMeshComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Tank), meta=(BlueprintSpawnableComponent))
class TANKWORLD_API UTankTrackMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable)
		void SetThrottle(float value);
	

	UPROPERTY(EditDefaultsOnly)
		float	MaxTankTrackDriveForcer = 400000.0f;
};
