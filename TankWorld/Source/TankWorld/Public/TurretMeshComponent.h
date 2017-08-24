// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TurretMeshComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class TANKWORLD_API UTurretMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
	
public:
	void Turn(float turnSpeed);

	UPROPERTY(EditDefaultsOnly, category = Setup)
		float		MaxTurnPerSecond = 25;
};
