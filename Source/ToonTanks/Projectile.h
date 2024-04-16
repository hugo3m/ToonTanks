// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

// forward declare class
class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	// object handling movement for projectile
	// class from unreal engine
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	// bind function to on hit event of primitive component
	// MUST BE A UFUNCTION
	void OnHit(
		UPrimitiveComponent* HitComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse,
		const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystemComponent* TrailParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	// not need to forward declare twice
	USoundBase* HitSound;

	void HandleDestruction();

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
};
