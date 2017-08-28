// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrelMeshComponent.h"
#include "TurretMeshComponent.h"
#include "Projectile.h"
#include "kismet/GameplayStatics.h"
#include "engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AmmoLeft <= 0) {
		FiringState = EFireStatus::AmmoExhausted;
	}
	else if (FPlatformTime::Seconds() - LastFireTime < FireInterval) {
		FiringState = EFireStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringState = EFireStatus::Aiming;
	}
	else {
		FiringState = EFireStatus::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrelMeshComponent* barrelToSet, UTurretMeshComponent* turretToSet) {
	BarrelComponent = barrelToSet;
	TurretComponent = turretToSet;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(ProjectileClass)) {
		return;
	}

	if (FiringState == EFireStatus::Locked || FiringState == EFireStatus::Aiming) {
		FVector location = BarrelComponent ->GetSocketLocation(FName(TEXT("ProjectileLocation")));
		FRotator rotation = BarrelComponent ->GetSocketRotation(FName(TEXT("ProjectileLocation")));
		AProjectile *projectile = GWorld->SpawnActor<AProjectile>(ProjectileClass, location, rotation);
		projectile->Launch(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
		FMath::Clamp(--AmmoLeft, 0, 3);
	}
}


void UTankAimingComponent::AimAt(const FVector & hitLocation)
{
	if (!BarrelComponent) {
		return;
	}

	FVector startLocation = BarrelComponent->GetSocketLocation(FName(TEXT("ProjectileLocation")));
	FVector outTossDirection;
	AimToDir = FVector::ZeroVector;
	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outTossDirection, startLocation, hitLocation, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace, FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(), false);
	
	if (bHasAimSolution) {
		AimToDir = outTossDirection.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s find aim solution"), *GetOwner()->GetName());
		MoveBarrelToward(AimToDir);
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s can't find aim solution"), *GetOwner()->GetName());
	}
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s fired! aim at %s"), *GetOwner()->GetName(), *aimDirection.ToString());
}

EFireStatus UTankAimingComponent::GetFireStatus() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetAmmoLeft() const
{
	return AmmoLeft;
}

void UTankAimingComponent::MoveBarrelToward(const FVector& dir)
{
	if (!BarrelComponent) {
		return;
	}
	FRotator cur0 = BarrelComponent->GetForwardVector().Rotation();
	FRotator dest = dir.Rotation();
	FRotator diff = dest - cur0;


	BarrelComponent->Elevate(diff.Pitch);

	if (FMath::Abs(diff.Yaw) < 180.0f)
	{
		TurretComponent->Turn(diff.Yaw);
	}
	else {
		TurretComponent->Turn(-diff.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(BarrelComponent)) {
		return false;
	}

	auto barrelForward = BarrelComponent->GetForwardVector();
	return !AimToDir.Equals(barrelForward, 0.01f);
}

