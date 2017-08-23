// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretMeshComponent.h"
#include "engine/world.h"

void UTurretMeshComponent::Turn(float turnSpeed) {
	turnSpeed = FMath::Clamp(turnSpeed, -1.0f, 1.0f);
	float turnDegree = turnSpeed * MaxTurnPerSecond * GetWorld()->DeltaTimeSeconds;
	turnDegree += RelativeRotation.Yaw;
	SetRelativeRotation(FRotator(0.0f, turnDegree, 0.0f));
}

