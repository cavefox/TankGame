// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelMeshComponent.h"
#include "engine/World.h"


void UTankBarrelMeshComponent::Elevate(float relativeSpeed) {
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);
	float pitchToElevate = relativeSpeed * MaxDegreesPerSecond * GWorld->DeltaTimeSeconds;
	float rawElevate = FMath::Clamp(RelativeRotation.Pitch + pitchToElevate, MinElevationDegree, MaxElevationDegree);
	SetRelativeRotation(FRotator(rawElevate, 0, 0));
}

