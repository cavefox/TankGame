// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackMeshComponent.h"
#include "components/PrimitiveComponent.h"



void UTankTrackMeshComponent::SetThrottle(float value) {
	//UE_LOG(LogTemp, Warning, TEXT("%s %s %f"), *GetOwner()->GetName(), *GetName(), value);
	
	FVector appliedForce = GetForwardVector() * value * MaxTankTrackDriveForcer;
	FVector location = GetComponentLocation();
	
	auto appliedBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (appliedBody) {
		appliedBody->AddForceAtLocation(appliedForce, location);
	}
}