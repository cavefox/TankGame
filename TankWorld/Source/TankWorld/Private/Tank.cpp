// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrelMeshComponent.h"
#include "engine/World.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName(TEXT("My Aiming Component")));
}

void ATank::AimAt(const FVector & hitLocation)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *GetName(), *hitLocation.ToString());
	if (!TankAimingComponent) {
		return;
	}


	TankAimingComponent->AimAt(hitLocation, LaunchSpeed);
}

void ATank::SetBarrelMeshComponent(UTankBarrelMeshComponent * BarrelToSet)
{
	if (!TankAimingComponent) {
		return;
	}

	BarrelComponent = BarrelToSet;
	TankAimingComponent->SetBarrelMeshComponent(BarrelToSet);
}

void ATank::SetTurretMeshComponent(UTurretMeshComponent * turretToSet)
{
	if (!TankAimingComponent) {
		return;
	}
	TankAimingComponent->SetTurretMeshComponent(turretToSet);
}

void ATank::Fire()
{
	if (!TankAimingComponent) {
		return;
	}

	if (!BarrelComponent) {
		return;
	}

	bool bReload = (FPlatformTime::Seconds() - LastFireTime) >= FireInterval;


	if (bReload) {
		FVector location = BarrelComponent->GetSocketLocation(FName(TEXT("ProjectileLocation")));
		FRotator rotation = BarrelComponent->GetSocketRotation(FName(TEXT("ProjectileLocation")));
		AProjectile *projectile = GWorld->SpawnActor<AProjectile>(ProjectileClass, location, rotation);
		projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

