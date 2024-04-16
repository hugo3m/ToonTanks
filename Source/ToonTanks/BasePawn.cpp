// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	// TODO: Visual/sounds effects
	if(DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			DeathParticle,
			GetActorLocation(),
			GetActorRotation()
		);
	}
	if(DeathSound)
	{
		// play hit sound
		UGameplayStatics::PlaySoundAtLocation(
			this,
			DeathSound,
			GetActorLocation()
		);
	}
	if(DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(
			DeathCameraShakeClass
		);
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	// world space location
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	// the rotation to look at
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0);
	// because look at target is world location, use set world
	// iterpolation allow to interpolate a rotation
	// i.e. smoothly make the rotation
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			5.f
			)
		);
}

void ABasePawn::Fire()
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass, 
		ProjectileSpawnPoint->GetComponentLocation(), 
		ProjectileSpawnPoint->GetComponentRotation());
	// set the owner of the projectile
	Projectile->SetOwner(this);
}


