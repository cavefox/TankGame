// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelMeshComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class TANKWORLD_API UTankBarrelMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float relativeSpeed);
	
	UPROPERTY(EditDefaultsOnly, category = Setup)
		float		MaxElevationDegree = 40;

	UPROPERTY(EditDefaultsOnly, category = Setup)
		float		MinElevationDegree = 0;

	UPROPERTY(EditDefaultsOnly, category = Setup)
		float		MaxDegreesPerSecond = 10;
};
