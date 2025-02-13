// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class TANKWORLD_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	void OnTimeExpire();

public:	

	void Launch(float speed);
	
protected:
	UPROPERTY(EditDefaultsOnly)
		UProjectileMovementComponent	*ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent		*CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent	*LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent	*ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
		URadialForceComponent		*ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly)
		float			DestroyDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly)
		float			DamageAmout = 1001.0f;

};
