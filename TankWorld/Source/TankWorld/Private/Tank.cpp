// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();


	ATank* DefaultObj = Cast<ATank>(GetClass()->GetDefaultObject());
	CurrentPoints = DefaultObj->FullHealthPoints;

	OnTakeAnyDamage.AddDynamic(this, &ATank::OnAnyDamage);
	OnTakePointDamage.AddDynamic(this, &ATank::OnPointDamage);
}

float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	auto name = GetName();
	float damageCalculateFromSuper = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	CurrentPoints = FMath::Clamp<float>(CurrentPoints - damageCalculateFromSuper, 0, FullHealthPoints);
	if (FMath::IsNearlyEqual(CurrentPoints, 0.0f)) {
		OnTankDead.Broadcast();
	}

	return damageCalculateFromSuper;
}

void ATank::OnAnyDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{

}

void ATank::OnPointDamage(AActor * DamagedActor, float Damage, AController * InstigatedBy, FVector HitLocation, UPrimitiveComponent * FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType * DamageType, AActor * DamageCauser)
{

}
