// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "engine/World.h"
#include "gameframework/PlayerController.h"
#include "gameframework/Actor.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (!ensure(GetPawn())) {
		return;
	}

	
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	AActor* target = GWorld->GetFirstPlayerController()->GetPawn();
	if (ensure(AimingComponent) && ensure(target)) {
		AimingComponent->AimAt(target->GetActorLocation());
		MoveToActor(target, PathFindingAcceptanceRadius);

		if(AimingComponent ->GetFireStatus() == EFireStatus::Locked)
			AimingComponent->Fire();
	}
	
}


void ATankAIController::Fire()
{
	/*
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	if (ControlledTank) {
		ControlledTank->Fire();
	}
	*/
}
