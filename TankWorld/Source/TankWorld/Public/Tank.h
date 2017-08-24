// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrelMeshComponent;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class TANKWORLD_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();


	void AimAt(const FVector& hitLocation);

	UFUNCTION(BlueprintCallable)
		void Fire();

protected:
	UPROPERTY()
		UTankAimingComponent*			TankAimingComponent;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AProjectile>		ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
		float		LaunchSpeed = 4500; // TODO 将Tank的LaunchSpeed设置为一个更合理的值 默认: 1公里/s 

	UFUNCTION(BlueprintCallable)
		void SetBarrelMeshComponent(UTankBarrelMeshComponent* BarrelToSet);

	UFUNCTION(BlueprintCallable)
		void SetTurretMeshComponent(class UTurretMeshComponent* turretToSet);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
private:
	UPROPERTY()
		UTankBarrelMeshComponent *BarrelComponent = nullptr;

	UPROPERTY(EditAnywhere)
		float	FireInterval = 3.0f;

	double LastFireTime = 0;
};
