// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this tank's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const;

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// no need of meta if not exposed to event graph
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 200.f;

	void MoveForward(float Value);

	void Turn(float Value);

	APlayerController* TankPlayerController;
};
