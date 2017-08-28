// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackMeshComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Tank), meta=(BlueprintSpawnableComponent))
class TANKWORLD_API UTankTrackMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

	UTankTrackMeshComponent();
	
	virtual void BeginPlay()override;

	void ApplySidewayForce();

protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	UFUNCTION(BlueprintCallable)
		void SetThrottle(float value);

	void MoveTrack();
	

	UPROPERTY(EditDefaultsOnly)
		float	MaxTankTrackDriveForcer = 400000.0f;

private:
	void ResetThrottleValue();
	float ThrottleValue = 0.0f;
};
