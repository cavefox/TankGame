// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "engine/world.h"
#include "runtime/Engine/Public/TimerManager.h"
#include "kismet/GameplayStatics.h"
#include "gameframework/DamageType.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Collision Mesh")));
	RootComponent = CollisionMesh;
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Launch Blast")));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Impact Blast")));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;


	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("ProjMovementComp")));
	ProjectileMovementComponent->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName(TEXT("Radial Force Component")));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{	
	CollisionMesh->DestroyComponent();
	LaunchBlast->Deactivate();
	ImpactBlast->Activate(true);
	ExplosionForce->FireImpulse();


	UGameplayStatics::ApplyRadialDamage(this, DamageAmout, Hit.Location, ExplosionForce ->Radius, UDamageType::StaticClass(), TArray<AActor*>());


	FTimerHandle th;
	GWorld->GetTimerManager().SetTimer(th,
		this,
		&AProjectile::OnTimeExpire,
		DestroyDelay,
		false,
		-1.0f);
}

void AProjectile::OnTimeExpire() {
	Destroy();
}

void AProjectile::Launch(float speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	ProjectileMovementComponent->Activate(true);
}

