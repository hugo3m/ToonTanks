// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	// int32 VisibleAnywhereInt = 12;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// int32 BlueprintReadOnlyInt = 12;

	// UPROPERTY(EditAnywhere)
	// int32 EditAnywhereInt = 12;

	// UPROPERTY(VisibleInstanceOnly)
	// int32 VisibleInstanceOnlyInt = 12;

	// UPROPERTY(VisibleDefaultsOnly)
	// int32 VisibleDefaultsOnlyInt = 12;

	// UPROPERTY(EditDefaultsOnly)
	// int32 EditDefaultsOnlyInt = 12;

	// UPROPERTY(EditInstanceOnly)
	// int32 EditInstanceOnlyInt = 12;

	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);

	void Fire();

private:
	// no need of meta if not exposed to event graph
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Super Variables", meta = (AllowPrivateAccess = "true"))
	// int32 VisibleAnywhereIntPrivate = 1


	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	// link a bp class to c++
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
