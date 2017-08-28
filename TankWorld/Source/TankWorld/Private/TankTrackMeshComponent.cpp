// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackMeshComponent.h"
#include "components/PrimitiveComponent.h"
#include "engine/world.h"

UTankTrackMeshComponent::UTankTrackMeshComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrackMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrackMeshComponent::OnHit);
}

void UTankTrackMeshComponent::ApplySidewayForce()
{
	float slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	FVector acceleration = -slippageSpeed * GWorld ->DeltaTimeSeconds * GetRightVector();

	// F = ma;
	auto tank = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	float mass = tank->GetMass();
	FVector force = acceleration * mass / 2.0f;

	//UE_LOG(LogTemp, Warning, TEXT("force: %s"), *force.ToString());

	tank->AddForce(force * 100);
}

void UTankTrackMeshComponent::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{

	//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.Actor ->GetName());
	ApplySidewayForce();
	MoveTrack();
	ResetThrottleValue();
}


void UTankTrackMeshComponent::SetThrottle(float value) {
	//UE_LOG(LogTemp, Warning, TEXT("%s %s %f"), *GetOwner()->GetName(), *GetName(), value);
	ThrottleValue += value;
	ThrottleValue = FMath::Clamp(ThrottleValue, -1.0f, 1.0f);
}

void UTankTrackMeshComponent::ResetThrottleValue() {
	ThrottleValue = 0.0f;
}

void UTankTrackMeshComponent::MoveTrack()
{
	FVector appliedForce = GetForwardVector() * ThrottleValue * MaxTankTrackDriveForcer;
	FVector location = GetComponentLocation();

	auto appliedBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (appliedBody) {
		appliedBody->AddForceAtLocation(appliedForce, location);
	}
}
