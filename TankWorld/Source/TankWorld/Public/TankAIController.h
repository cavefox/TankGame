// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class TANKWORLD_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime)override;
	
public:
	UFUNCTION(BlueprintCallable)
		void Fire();


	UPROPERTY(EditAnywhere)
		float PathFindingAcceptanceRadius = 3000.0f;
};
