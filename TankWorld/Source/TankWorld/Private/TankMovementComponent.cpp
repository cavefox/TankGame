// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void	UTankMovementComponent::IntendToMoveForward(float throwValue) {
	if (!LeftTrack || !RightTrack) {
		return;
	}

	LeftTrack->SetThrottle(throwValue);
	RightTrack->SetThrottle(throwValue);
}

void	UTankMovementComponent::IntendToTurnRight(float throwValue) {
	if (!LeftTrack || !RightTrack) {
		return;
	}

	LeftTrack->SetThrottle(throwValue);
	RightTrack->SetThrottle(-throwValue);
}


void	UTankMovementComponent::Initialise(UTankTrackMeshComponent* leftTrack, UTankTrackMeshComponent* rightTrack) {
	LeftTrack = leftTrack;
	RightTrack = rightTrack;
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	auto aiUnitVec = MoveVelocity.SafeNormal();
	auto tankForwardVec = GetOwner()->GetActorForwardVector();


	auto RequestForwardThrow = FVector::DotProduct(tankForwardVec, aiUnitVec);
	auto RequestTurnThrow = FVector::CrossProduct(tankForwardVec, aiUnitVec);


	IntendToMoveForward(RequestForwardThrow);
	IntendToTurnRight(RequestTurnThrow.Z);
}