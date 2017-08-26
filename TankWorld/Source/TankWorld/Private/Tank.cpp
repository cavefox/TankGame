// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrelMeshComponent.h"
#include "engine/World.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("Tank C++ Construct"));
}

void ATank::AimAt(const FVector & hitLocation)
{
	UTankAimingComponent *AimingComponent = FindComponentByClass<UTankAimingComponent>();
	if (!AimingComponent) {
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *GetName(), *hitLocation.ToString());

	AimingComponent ->AimAt(hitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	UTankAimingComponent *AimingComponent = FindComponentByClass<UTankAimingComponent>();
	if (!AimingComponent) {
		return;
	}


	bool bReload = (FPlatformTime::Seconds() - LastFireTime) >= FireInterval;


	if (bReload) {
		FVector location = AimingComponent ->GetBarrelMeshComponent() ->GetSocketLocation(FName(TEXT("ProjectileLocation")));
		FRotator rotation = AimingComponent->GetBarrelMeshComponent() ->GetSocketRotation(FName(TEXT("ProjectileLocation")));
		AProjectile *projectile = GWorld->SpawnActor<AProjectile>(ProjectileClass, location, rotation);
		projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Tank C++ BeginPlay"));
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

