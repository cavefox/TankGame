// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Gameframework/Actor.h"
#include "components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelMeshComponent(UStaticMeshComponent * ComponentToSet)
{
	BarrelComponent = ComponentToSet;
}

void UTankAimingComponent::AimAt(const FVector & hitLocation)
{
	auto from = BarrelComponent->GetComponentLocation().ToString();
	auto to = hitLocation.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Tank %s aim target form %s to %s"), *GetOwner()->GetName(), *from, *to);
}

