// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrelMeshComponent;
class UTurretMeshComponent;


UENUM(BlueprintType)
enum class EFireStatus : uint8 {
	Reloading = 0,
	Aiming,
	Locked
};

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
	UFUNCTION(BlueprintCallable)
		void Initialise(UTankBarrelMeshComponent* barrelToSet, UTurretMeshComponent* turretToSet);
		
	void AimAt(const FVector& hitLocation, float launchSpeed);

	UTankBarrelMeshComponent* GetBarrelMeshComponent()const {
		return BarrelComponent;
	}

	UTurretMeshComponent* GetTurretMeshComponent()const {
		return TurretComponent;
	}

protected:
	UPROPERTY(BlueprintReadOnly)
		EFireStatus		FiringState = EFireStatus::Locked;

private:
	void MoveBarrelToward(const FVector& dir);

	UPROPERTY()
	UTankBarrelMeshComponent* BarrelComponent;

	UPROPERTY()
	UTurretMeshComponent*	TurretComponent;
};
