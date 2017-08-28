// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/Engine.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TankAimingComponent.h"

#define OUT

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	//ATank* possessedTank = GetControlledTank();

	UTankAimingComponent* AimingComponent = GetPawn() ->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent) {
		FindTankAimingComponent(AimingComponent);
	}
	else {
		auto tankName = GetPawn()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s can't find AimingComponent"), *tankName);
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) {
		return;
	}

	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FVector hitLocation = FVector::ZeroVector;
		if (GetRaySightHitLocation(OUT hitLocation)) {
			AimingComponent->AimAt(hitLocation);
			//UE_LOG(LogTemp, Warning, TEXT("Tank %s Find hit location"), *GetControlledTank() ->GetName());
			//tank->AimAt(hitLocation);
		}
		else {
			//UE_LOG(LogTemp, Warning, TEXT("Tank %s Can't Find hit location"), *GetControlledTank()->GetName());
		}
	}

}

bool ATankPlayerController::GetRaySightHitLocation(FVector& outHitLocation)const {

	int32 viewportSizeX = 0;
	int32 viewportSizeY = 0;
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D crosshairScreenPos = FVector2D(viewportSizeX * CrosshairInScreenPositionRatioX, viewportSizeY * CrosshairInScreenPositionRatioY);
	FVector lookDirection = FVector::ZeroVector;
	if (GetLookDirection(crosshairScreenPos, lookDirection)) {
		if (GetLookVectorHitResult(lookDirection, outHitLocation)) {
			return true;
		}
	}

	return false;
};

bool ATankPlayerController::GetLookDirection(FVector2D screenPos, FVector& lookDirection)const {
	FVector worldPosition;
	return DeprojectScreenPositionToWorld(screenPos.X,
		screenPos.Y,
		worldPosition,
		lookDirection);
}

bool ATankPlayerController::GetLookVectorHitResult(FVector lookDirection, FVector& hitLocation) const{
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + SightRangeToTrace * lookDirection;
	FHitResult hitResult;
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetPawn());
	if (GWorld->LineTraceSingleByChannel(OUT hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility,
		queryParams)) {
		hitLocation = hitResult.Location;
		return true;
	}
	hitLocation = FVector::ZeroVector;
	return false;
}