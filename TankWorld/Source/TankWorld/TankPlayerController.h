// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class TANKWORLD_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION()
		void OnTankDead();

public:
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime)override;
	virtual void SetPawn(APawn* InPawn)override;



	UFUNCTION(BlueprintImplementableEvent)
		void FindTankAimingComponent(UTankAimingComponent* AimingComponent);


	void AimTowardsCrosshair();
	bool GetRaySightHitLocation(FVector& outHitLocation)const;
	bool GetLookDirection(FVector2D screenPos, FVector& lookDirection)const;
	bool GetLookVectorHitResult(FVector lookDirection, FVector& hitLocation)const;

	UPROPERTY(EditDefaultsOnly)
		float		SightRangeToTrace = 1000000.0f;

	UPROPERTY(EditDefaultsOnly)
		float		CrosshairInScreenPositionRatioX = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float		CrosshairInScreenPositionRatioY = 0.3f;

};
