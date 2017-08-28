// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrelMeshComponent;
class UTurretMeshComponent;
class AProjectile;

UENUM(BlueprintType)
enum class EFireStatus : uint8 {
	Reloading = 0,
	Aiming,
	Locked,
	AmmoExhausted,
};

UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent) )
class TANKWORLD_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)override;

public:	
	UFUNCTION(BlueprintCallable)
		void Initialise(UTankBarrelMeshComponent* barrelToSet, UTurretMeshComponent* turretToSet);

	UFUNCTION(BlueprintCallable)
		void Fire();
		
	void AimAt(const FVector& hitLocation);

	UTankBarrelMeshComponent* GetBarrelMeshComponent()const {
		return BarrelComponent;
	}

	UTurretMeshComponent* GetTurretMeshComponent()const {
		return TurretComponent;
	}

	EFireStatus GetFireStatus()const;

	UFUNCTION(BlueprintCallable)
		int32 GetAmmoLeft()const;

protected:

	//	��ǰ״̬
	UPROPERTY(BlueprintReadOnly)
		EFireStatus		FiringState = EFireStatus::Reloading;

	//  �����ʼ�ٶ�
	UPROPERTY(EditDefaultsOnly)
		float		LaunchSpeed = 4500; // TODO ��Tank��LaunchSpeed����Ϊһ���������ֵ Ĭ��: 1����/s 


	//	�ڵ���
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AProjectile>		ProjectileClass;

	//	������
	UPROPERTY(EditAnywhere)
		float	FireInterval = 3.0f;

	UPROPERTY(EditAnywhere)
	int32	AmmoLeft = 999;


private:
	void MoveBarrelToward(const FVector& dir);
	bool IsBarrelMoving();

	UPROPERTY()
	UTankBarrelMeshComponent* BarrelComponent;

	UPROPERTY()
	UTurretMeshComponent*	TurretComponent;

	double LastFireTime = 0;
	FVector AimToDir = FVector::ZeroVector;
};
