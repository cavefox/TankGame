// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTankDeadDelegate);

class UTankBarrelMeshComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class TANKWORLD_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;

	UFUNCTION(BlueprintCallable)
	float	GetHealthPointPercent()const { return CurrentPoints / FullHealthPoints; }

	UPROPERTY()
		FOnTankDeadDelegate			OnTankDead;

protected:
	UFUNCTION()
	void OnAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

	UFUNCTION()
	void OnPointDamage(	AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser );

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float		FullHealthPoints = 10000.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float	CurrentPoints = FullHealthPoints;
};
