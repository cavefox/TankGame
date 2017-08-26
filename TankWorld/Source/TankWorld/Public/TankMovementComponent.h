// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrackMeshComponent;

/**
 * 
 */
UCLASS(ClassGroup=(Tank), meta=(BlueprintSpawnableComponent))
class TANKWORLD_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void	Initialise(UTankTrackMeshComponent* leftTrack, UTankTrackMeshComponent* rightTrack);

	UFUNCTION(BlueprintCallable)
	void	IntendToMoveForward(float throwValue);

	UFUNCTION(BlueprintCallable)
	void IntendToTurnRight(float throwValue);

	
protected:
	UPROPERTY()
		UTankTrackMeshComponent *LeftTrack;
	UPROPERTY()
		UTankTrackMeshComponent *RightTrack;


private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)override;
};
