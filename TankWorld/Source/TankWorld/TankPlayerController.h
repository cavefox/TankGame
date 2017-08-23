// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;

/**
 * 
 */
UCLASS()
class TANKWORLD_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime)override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ATank* GetControlledTank()const;
	void AimTowardsCrosshair();

	bool GetRaySightHitLocation(FVector& outHitLocation)const;
	bool GetLookDirection(FVector2D screenPos, FVector& lookDirection)const;
	bool GetLookVectorHitResult(FVector lookDirection, FVector& hitLocation)const;

	UPROPERTY(EditAnywhere)
		float		SightRangeToTrace = 1000000.0f;

	UPROPERTY(EditAnywhere)
		float		CrosshairInScreenPositionRatioX = 0.5f;

	UPROPERTY(EditAnywhere)
		float		CrosshairInScreenPositionRatioY = 0.3f;

};
