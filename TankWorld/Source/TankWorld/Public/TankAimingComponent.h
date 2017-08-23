// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrelMeshComponent;
class UTurretMeshComponent;

UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent) )
class TANKWORLD_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

		
	void SetBarrelMeshComponent(UTankBarrelMeshComponent* ComponentToSet);
	void SetTurretMeshComponent(UTurretMeshComponent* turretToSet);
	void AimAt(const FVector& hitLocation, float launchSpeed);
private:
	void MoveBarrelToward(const FVector& dir);

	UPROPERTY()
	UTankBarrelMeshComponent* BarrelComponent;

	UPROPERTY()
	UTurretMeshComponent*	TurretComponent;
};
