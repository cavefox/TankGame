// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrelMeshComponent;
class UTankAimingComponent;

UCLASS()
class TANKWORLD_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();


	void AimAt(const FVector& hitLocation);

protected:
	UPROPERTY()
		UTankAimingComponent*			TankAimingComponent;

	UPROPERTY(EditAnywhere)
		float		LaunchSpeed = 4500; // TODO ��Tank��LaunchSpeed����Ϊһ���������ֵ Ĭ��: 1����/s 

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

	
	
};
