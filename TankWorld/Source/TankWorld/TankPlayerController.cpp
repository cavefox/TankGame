// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/Engine.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/KismetSystemLibrary.h"

#define OUT

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	ATank* possessedTank = GetControlledTank();

	if (!possessedTank) {
		UE_LOG(LogTemp, Warning, TEXT("[[ATankPlayerController]]   TankPlayerController not possess a tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[[ATankPlayerController]]   TankPlayerController is possessing %s"), *possessedTank ->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank()const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (GetControlledTank() == nullptr) {
		return;
	}

	FVector hitLocation = FVector::ZeroVector;
	if(GetRaySightHitLocation( OUT hitLocation )){
		auto tank = GetControlledTank();
		tank->AimAt(hitLocation);
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
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetControlledTank());
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