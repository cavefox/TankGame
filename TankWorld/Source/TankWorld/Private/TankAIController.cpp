// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "engine/World.h"
#include "gameframework/PlayerController.h"
#include "Tank.h"


void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	//GetControlledTank()->AimAt(GetPlayerControlledTank()->GetActorLocation());

	ATank* ControlledTank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank>(GWorld->GetFirstPlayerController()->GetPawn());

	if (PlayerTank && ControlledTank) {
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//Fire();

		MoveToActor(PlayerTank, PathFindingAcceptanceRadius);
	}
	
}


void ATankAIController::Fire()
{
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	if (ControlledTank) {
		ControlledTank->Fire();
	}
}
