// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "engine/World.h"
#include "gameframework/PlayerController.h"




void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* PlayerTank = GetPlayerControlledTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("[[ATankAIController]]   TankAIController can't find the player tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[[ATankAIController]]   TankAIController find the player tank %s"), *PlayerTank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank()const {
	return Cast<ATank>(GetControlledPawn());
}

ATank* ATankAIController::GetPlayerControlledTank()const {
	return Cast<ATank>(GWorld->GetFirstPlayerController()->GetControlledPawn());
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	GetControlledTank()->AimAt(GetPlayerControlledTank()->GetActorLocation());
}