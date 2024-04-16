// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;

	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail particle"));
	TrailParticle->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	// bind function to hit
	// MUST BE DONE IN BEGIN PLAY
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	// play launch sound
	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			LaunchSound,
			GetActorLocation()
		);
	}
}

void AProjectile::OnHit(
		UPrimitiveComponent* HitComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse,
		const FHitResult& Hit)
{
	// owner has been set by basepawn when firing
	AActor* Owner = GetOwner();
	// if hitting other actor and not this and the other actor is not this owner
	if(Owner && OtherActor && OtherActor != this && OtherActor != Owner)
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			Owner->GetInstigatorController(),
			this,
			UDamageType::StaticClass()
		);
		if(HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(
				HitCameraShakeClass
			);
		}
	}
	HandleDestruction();
}

void AProjectile::HandleDestruction()
{
	// if hit particle
	if(HitParticle)
	{
		// spawn particle
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			HitParticle,
			GetActorLocation(),
			GetActorRotation()
		);
	}
	// if hit sound
	if(HitSound)
	{
		// play hit sound
		UGameplayStatics::PlaySoundAtLocation(
			this,
			HitSound,
			GetActorLocation()
		);
	}
	Destroy();
}

