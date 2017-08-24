// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Gameframework/Actor.h"
#include "components/StaticMeshComponent.h"
#include "TankBarrelMeshComponent.h"
#include "TurretMeshComponent.h"
#include "kismet/GameplayStatics.h"
#include "engine/World.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UTankAimingComponent::SetBarrelMeshComponent(UTankBarrelMeshComponent * ComponentToSet)
{
	BarrelComponent = ComponentToSet;
}

void UTankAimingComponent::SetTurretMeshComponent(UTurretMeshComponent * turretToSet)
{
	TurretComponent = turretToSet;
}

void UTankAimingComponent::AimAt(const FVector & hitLocation, float launchSpeed)
{
	if (!BarrelComponent) {
		return;
	}

	FVector startLocation = BarrelComponent->GetSocketLocation(FName(TEXT("ProjectileLocation")));
	FVector outTossDirection;
	FVector aimDirection = FVector::ZeroVector;
	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outTossDirection, startLocation, hitLocation, launchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace, FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(), false);
	
	if (bHasAimSolution) {
		aimDirection = outTossDirection.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s find aim solution"), *GetOwner()->GetName());
		MoveBarrelToward(aimDirection);
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s can't find aim solution"), *GetOwner()->GetName());
	}
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s fired! aim at %s"), *GetOwner()->GetName(), *aimDirection.ToString());
}

void UTankAimingComponent::MoveBarrelToward(const FVector& dir)
{
	if (!BarrelComponent) {
		return;
	}
	FVector cameraRightVec = GWorld->GetFirstPlayerController()->PlayerCameraManager->GetActorRightVector();
	FVector2D rightVec2D = FVector2D(-cameraRightVec.X, -cameraRightVec.Y);
	FVector2D dir2D = FVector2D(BarrelComponent->GetForwardVector().X, BarrelComponent->GetForwardVector().Y);


	FRotator cur0 = BarrelComponent->GetForwardVector().Rotation();
	FRotator cur = BarrelComponent->GetRelativeTransform().GetRotation().Rotator();
	FRotator dest = dir.Rotation();
	FRotator diff = dest - cur0;

	//UE_LOG(LogTemp, Warning, TEXT("Tank %s dest Yaw %f"), *GetOwner()->GetName(), dest.Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s cur Yaw %f"), *GetOwner()->GetName(), cur0.Yaw);
	BarrelComponent->Elevate(diff.Pitch);
	//TurretComponent->Turn(FVector2D::DotProduct(dir2D, rightVec2D) * 5.0f);
	TurretComponent->Turn(diff.Yaw);
}

